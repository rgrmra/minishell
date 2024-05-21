/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:09:08 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/21 13:52:11 by rde-mour         ###   ########.org.br   */
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
	if ((ft_strchr("./", *cmd) || cmd[ft_strlen(cmd) - 1] == '/')
		&& error != ENOENT && path_stat.st_mode & S_IFDIR)
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

static void	execution(t_env *env, char **cmd)
{
	char	**tmp;

	tmp = envexport(env->vars);
	if (access(*cmd, F_OK) < 0)
		panic(*cmd, NULL, "No such file or directory", ENOENT);
	else if (access(*cmd, X_OK) < 0)
		panic(*cmd, NULL, "Permission Denied", EACCES);
	else if (execve(*cmd, cmd, tmp) < 0)
		panic(*cmd, NULL, strerror(errno), errno);
	ft_freesplit(tmp);
}

static void	exec_subtree(t_env *env, char **cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		rl_clear_history();
		execution(env, cmd);
		ft_freesplit(cmd);
		clearall(env);
	}
	waitpid(pid, &status, WUNTRACED);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl("Quit (core dumped)");
		g_status = 128 + WTERMSIG(status);
	}
	else
		g_status = WEXITSTATUS(status);
}

void	execute_command(t_env *env, t_ast *ast)
{
	char	**cmd;

	if (!ast)
		return ;
	var_expansions(env, &ast->content->literal);
	if (!ast->content->literal[0])
	{
		g_status = 0;
		return ;
	}
	cmd = ft_strtok(ast->content->literal, ' ');
	remove_quotes(cmd);
	command_expansions(env, cmd);
	if (execute_builtin(env, cmd))
		return ;
	if (*cmd && **cmd && (**cmd == '/' || ft_strncmp(*cmd, "./", 2) == 0
			|| cmd[0][ft_strlen(*cmd) - 1] == '/'))
		exec_subtree(env, cmd);
	else
		panic(*cmd, NULL, "command not found", ENOENT);
	ft_freesplit(cmd);
}
