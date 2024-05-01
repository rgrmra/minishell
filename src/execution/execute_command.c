/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:09:08 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/01 10:55:37 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "execution.h"
#include "ft_hashmap.h"
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

static int	execute_builtin(t_env *env, t_ast **ast, char **cmd, int *fds, int *std)
{
	t_exec_func	builtin;

	if (ft_strncmp(*cmd, "exit", 5) == 0)
	{
		ast_clear(ast);
		envclear(&(env->vars));
		ft_hshfree(env->builtins);
		forked(true);
		closeall(fds, std);
		builtin_exit(cmd);
	}
	builtin = ft_hshget(env->builtins, *cmd);
	if (!builtin)
		return (false);
	ast_clear(ast);
	open_stdout(fds);
	builtin(cmd, fds);
	closeall(fds, std);
	return (true);
}

static void	exec_subtree(t_env *env, char **cmd, int *fds, int *std)
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
				closeall(fds, std), exit(126));
		ft_freesplit(cmd);
		envclear(&(env->vars));
		ft_hshfree(env->builtins);
		printf("command not found!\n");
		closeall(fds, std);
		exit(127);
	}
	if (forked(false))
		closeall(fds, std);
	waitpid(pid, &status, WUNTRACED);
	g_status = WEXITSTATUS(status);
}

void	execute_command(t_env *env, t_ast **ast, int *fds, int *std)
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
	if (execute_builtin(env, ast, cmd, fds, std))
		return ;
	exec_subtree(env, cmd, fds, std);
	ft_freesplit(cmd);
}
