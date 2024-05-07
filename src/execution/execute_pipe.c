/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:57:29 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/05 15:25:23 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

void	exec_left_subtree(t_env *env, t_ast *ast, int *fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		rl_clear_history();
		dup2(fds[1], STDOUT_FILENO);
		closeall(fds);
		execute(env, ast->left, fds);
		clearall(env);
	}
}

void	exec_right_subtree(t_env *env, t_ast *ast, int *fds)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		rl_clear_history();
		dup2(fds[0], STDIN_FILENO);
		closeall(fds);
		execute(env, ast->right, fds);
		clearall(env);
	}
	closeall(fds);
	waitpid(pid, &status, WUNTRACED);
	g_status = WEXITSTATUS(status);
}

void	execute_pipe(t_env *env, t_ast *ast)
{
	int	fds[4];

	pipe(fds);
	fds[2] = -2;
	fds[2] = -2;
	exec_left_subtree(env, ast, fds);
	exec_right_subtree(env, ast, fds);
}
