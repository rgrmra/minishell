/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:57:29 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/03 20:35:20 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "get_env.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

void	exec_lsubtree(t_env *env, t_ast *ast, int *lfds)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		rl_clear_history();
		dup2(lfds[1], STDOUT_FILENO);
		close(lfds[0]);
		close(lfds[1]);
		execute(env, ast->left, lfds);
		ast_clear(env->ast);
		envclear(&(env->vars));
		ft_hshfree(env->builtins);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit(g_status);
	}
}

void	exec_rsubtree(t_env *env, t_ast *ast, int *lfds)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		rl_clear_history();
		dup2(lfds[0], STDIN_FILENO);
		close(lfds[0]);
		close(lfds[1]);
		execute(env, ast->right, lfds);
		ast_clear(env->ast);
		envclear(&(env->vars));
		ft_hshfree(env->builtins);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit(g_status);
	}
	closeall(lfds);
	waitpid(pid, &status, WUNTRACED);
	g_status = WEXITSTATUS(status);
}

void	execute_pipe(t_env *env, t_ast *ast, int *lfds)
{
	int		*fds;

	free(lfds);
	fds = alloc_fds();
	pipe(fds);
	exec_lsubtree(env, ast, fds);
	exec_rsubtree(env, ast, fds);
}
