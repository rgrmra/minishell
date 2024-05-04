/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:09:08 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/04 14:11:43 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "builtin.h"
#include "execution.h"
#include "ft_hashmap.h"
#include "ft_string.h"
#include "prompt.h"
#include "types.h"
#include "utils.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

static int	execute_builtin(t_env *env, char **cmd, int *fds)
{
	t_exec_func	builtin;

	if (ft_strncmp(*cmd, "exit", 5) == 0)
		builtin_exit(env, cmd);
	builtin = ft_hshget(env->builtins, *cmd);
	if (!builtin)
		return (false);
	builtin(cmd, fds);
	closeall(fds);
	return (true);
}

static void	exec_subtree(t_env *env, char **cmd, int *fds)
{
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
		if (*cmd && (ft_strchr("./", **cmd) || access(*cmd, F_OK | X_OK) == 0)
			&& execve(*cmd, cmd, env->environ) < 0)
			(printf("minishell: %s: %s\n", *cmd, strerror(errno)),
				ft_freesplit(cmd), g_status = 126, clearall(env));
		printf("minishell: %s: command not found!\n", *cmd);
		ft_freesplit(cmd);
		g_status = 127;
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
