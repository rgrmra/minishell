/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:09:08 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/19 00:19:30 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "expansions.h"
#include "ft_hashmap.h"
#include "ft_string.h"
#include "get_env.h"
#include "types.h"
#include "ft_stdio.h"
#include "utils.h"
#include <asm-generic/errno-base.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <termios.h>

extern volatile sig_atomic_t	g_status;

void	panic(char *cmd, char *flag, char *message, int error)
{
	struct stat	path_stat;

	path_stat = (struct stat){0};
	stat((const char *) cmd, &path_stat);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (flag)
	{
		ft_putstr_fd(flag, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (error != 127 && path_stat.st_mode & S_IFDIR)
		ft_putendl_fd("Is a directory", STDERR_FILENO);
	else
		ft_putendl_fd(message, STDERR_FILENO);
	if (error == EACCES)
		g_status = 126;
	else if (error == ENOENT)
		g_status = 127;
	else
		g_status = error;
}

static int	execute_builtin(t_env *env, char **cmd)
{
	t_exec_func	builtin;

	builtin = ft_hshget(env->builtins, *cmd);
	if (!builtin)
		return (false);
	builtin(env, cmd);
	ft_freesplit(cmd);
	return (true);
}

static void	exec_subtree(t_env *env, char **cmd)
{
	char	**tmp;
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		g_status = 0;
		rl_clear_history();
		tmp = envexport(env->vars);
		if (*cmd && access(*cmd, F_OK) == 0 && execve(*cmd, cmd, tmp) < 0)
			panic(*cmd, NULL, strerror(errno), errno);
		else
			panic(*cmd, NULL, "command not found", errno);
		ft_freesplit(tmp);
		ft_freesplit(cmd);
		clearall(env);
	}
	waitpid(pid, &status, WUNTRACED);
	g_status = WEXITSTATUS(status);
}

void	execute_command(t_env *env, t_ast *ast)
{
	char			**cmd;
	struct termios	fd;

	if (!ast)
		return ;
	fd = (struct termios){0};
	tcgetattr(STDIN_FILENO, &fd);
	var_expansions(env, ast->content);
	cmd = ft_strtok(ast->content->literal, ' ');
	remove_quotes(cmd);
	command_expansions(env, cmd);
	if (execute_builtin(env, cmd))
		return ;
	exec_subtree(env, cmd);
	ft_freesplit(cmd);
	tcsetattr(STDIN_FILENO, 0, &fd);
}
