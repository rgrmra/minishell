/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:09:08 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/08 19:14:06 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "ft_hashmap.h"
#include "ft_string.h"
#include "get_env.h"
#include "prompt.h"
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

extern volatile sig_atomic_t	g_status;

void	panic(char *cmd, char *flag, char *message, int error)
{
	struct stat	path_stat;

	ft_memset(&path_stat, '\0', sizeof(path_stat));
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

static int	execute_builtin(t_env *env, char **cmd, int *fds)
{
	t_exec_func	builtin;

	builtin = ft_hshget(env->builtins, *cmd);
	if (!builtin)
		return (false);
	builtin(env, cmd);
	ft_freesplit(cmd);
	closeall(fds);
	return (true);
}

static void	exec_subtree(t_env *env, char **cmd, int *fds)
{
	char	**teste;
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0 && cmd)
	{
		rl_clear_history();
		closeall(fds);
		close(3);
		close(4);
		teste = envexport(env->vars);
		if (*cmd && execve(*cmd, cmd, teste) < 0)
			panic(*cmd, NULL, strerror(errno), errno);
		ft_freesplit(teste);
		ft_freesplit(cmd);
		clearall(env);
	}
	closeall(fds);
	waitpid(pid, &status, WUNTRACED);
	g_status = WEXITSTATUS(status);
}

void	execute_command(t_env *env, t_ast *ast, int *fds)
{
	char	**cmd;
	int		i;

	if (!ast)
		return ;
	var_expansions(env, ast->content);
	find_quote(ast->content->literal);
	cmd = ft_split(ast->content->literal, ' ');
	command_expansions(env, cmd);
	remove_quotes(cmd);
	i = 0;
	while (cmd[i])
		strrplc(cmd[i++], 0x1A, ' ');
	if (execute_builtin(env, cmd, fds))
		return ;
	exec_subtree(env, cmd, fds);
	ft_freesplit(cmd);
}
