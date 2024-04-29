/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:57:29 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 20:54:15 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "get_env.h"
#include "types.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

static void	exec_lsubtree(t_env *env, t_ast **ast, t_ast **clear, int *lfds)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		forked(true);
		ast_clear(clear);
		dup2(lfds[1], STDOUT_FILENO);
		close(lfds[0]);
		close(lfds[1]);
		execute(env, ast, lfds);
		envclear(&(env->vars));
		ft_hshfree(env->builtins);
		exit(g_status);
	}
}

static void	exec_rsubtree(t_env *env, t_ast **ast, t_ast **clear, int *lfds)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		forked(true);
		ast_clear(clear);
		dup2(lfds[0], STDIN_FILENO);
		close(lfds[0]);
		close(lfds[1]);
		execute(env, ast, lfds);
		envclear(&(env->vars));
		ft_hshfree(env->builtins);
		exit(g_status);
	}
	closeall(lfds);
	waitpid(pid, &status, WUNTRACED);
	g_status = WEXITSTATUS(status);
}

void	execute_pipe(t_env *env, t_ast **ast, int *lfds)
{
	int		*fds;
	t_ast	*left;
	t_ast	*right;

	free(lfds);
	fds = alloc_fds();
	left = (*ast)->left;
	right = (*ast)->right;
	ast_remove(ast);
	pipe(fds);
	exec_lsubtree(env, &left, &right, fds);
	exec_rsubtree(env, &right, &left, fds);
	ast_clear(&left);
	ast_clear(&right);
}
