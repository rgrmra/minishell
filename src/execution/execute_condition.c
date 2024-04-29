/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_condition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:43:52 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 20:53:55 by rde-mour         ###   ########.org.br   */
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

static void	exec_subtree(t_env *env, t_ast **ast, t_ast **clear)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		forked(true);
		ast_clear(clear);
		execute(env, ast, NULL);
		envclear(&(env->vars));
		ft_hshfree(env->builtins);
		exit(g_status);
	}
	waitpid(pid, &status, WUNTRACED);
	g_status = WEXITSTATUS(status);
}

void	execute_condition(t_env *env, t_ast **ast, int *fds)
{
	int		token;
	t_ast	*left;
	t_ast	*right;

	free(fds);
	token = (*ast)->content->type;
	left = (*ast)->left;
	right = (*ast)->right;
	ast_remove(ast);
	exec_subtree(env, &left, &right);
	if ((g_status == 0 && token & AND) || (g_status > 0 && token & OR))
		exec_subtree(env, &right, &left);
	ast_clear(&left);
	ast_clear(&right);
}
