/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:09:08 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/03 21:00:47 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "builtin.h"
#include "execution.h"
#include "ft_hashmap.h"
#include "ft_string.h"
#include "get_env.h"
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

static int	execute_builtin(t_env *env, t_ast *ast, char **cmd, int *fds)
{
	t_exec_func	builtin;

	if (ft_strncmp(*cmd, "exit", 5) == 0)
	{
		ast_clear(ast);
		envclear(&(env->vars));
		ft_hshfree(env->builtins);
		closeall(fds);
		builtin_exit(cmd);
	}
	builtin = ft_hshget(env->builtins, *cmd);
	if (!builtin)
		return (false);
	ast_clear(ast);
	open_stdout(fds);
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
		//open_stdout(fds);
		closeall(fds);
		close(4);
		close(3);
		ast_clear(env->ast);
		if (*cmd && (ft_strchr("./", **cmd) || access(*cmd, F_OK | X_OK) == 0)
			&& execve(*cmd, cmd, env->environ) < 0)
			(printf("minishell: %s: %s\n", *cmd, strerror(errno)),
				ft_freesplit(cmd), envclear(&(env->vars)),
				close(STDIN_FILENO), close(STDOUT_FILENO), close(STDERR_FILENO),
				closeall(fds),ft_hshfree(env->builtins), exit(126));
		printf("minishell: %s: command not found!\n", *cmd);
		ft_freesplit(cmd);
		envclear(&(env->vars));
		ft_hshfree(env->builtins);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit(127);
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
	find_quote(ast->content->literal);
	var_expansions(env, ast->content);
	cmd = ft_split(ast->content->literal, ' ');
	command_expansions(env, cmd);
	remove_quotes(cmd);
	i = 0;
	while (cmd[i])
		strrplc(cmd[i++], 0x1A, ' ');
	if (execute_builtin(env, ast, cmd, fds))
		return ;
	exec_subtree(env, cmd, fds);
	ft_freesplit(cmd);
}
