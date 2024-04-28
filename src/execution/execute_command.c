/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:09:08 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 18:37:37 by rde-mour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "execution.h"
#include "ft_string.h"
#include "get_env.h"
#include "prompt.h"
#include "types.h"
#include "utils.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

#include <stdio.h>

static int	execute_builtin(t_env *env, t_ast **ast, char **cmd, int *fds)
{
	if (builtin_exit(env, ast, cmd, fds))
		return (true);
	return (false);
}

static void	open_stdout(int *fds)
{
	if (fds && fds[2] > -1)
	{
		dup2(fds[2], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		return ;
	}
}

static void	exec_subtree(t_env *env, char **cmd, int *fds)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0 && cmd)
	{
		forked(true);
		open_stdout(fds);
		if (*cmd && (ft_strchr("./", **cmd) || access(*cmd, F_OK | X_OK) == 0)
			&& execve(*cmd, cmd, env->environ) < 0)
			(printf("failed!\n"), ft_freesplit(cmd), envclear(&(env->vars)),
				closeall(fds), exit(126));
		ft_freesplit(cmd);
		envclear(&(env->vars));
		printf("command not found!\n");
		closeall(fds);
		exit(127);
	}
	closeall(fds);
	waitpid(pid, &status, WUNTRACED);
	g_status = WEXITSTATUS(status);
}

void	execute_command(t_env *env, t_ast **ast, int *fds)
{
	char	**cmd;
	int		i;

	if (!ast || !(*ast))
		return ;
	find_quote((*ast)->content->literal);
	var_expansions(env, (*ast)->content);
	cmd = ft_split((*ast)->content->literal, ' ');
	command_expansions(env, cmd);
	remove_quotes(cmd);
	ast_remove(ast);
	i = 0;
	while (cmd[i])
		strrplc(cmd[i++], 0x1A, ' ');
	if (execute_builtin(env, ast, cmd, fds))
		return ;
	exec_subtree(env, cmd, fds);
	ft_freesplit(cmd);
}
