/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:50:33 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 19:16:49 by rde-mour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "get_env.h"
#include "types.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

static void	exec_subtree(t_env *env, t_ast **ast, t_ast **clear, int *lfds)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		forked(true);
		ast_clear(clear);
		execute(env, ast, lfds);
		envclear(&(env->vars));
		exit(g_status);
	}
	waitpid(pid, &status, WUNTRACED);
	g_status = WEXITSTATUS(status);
}

void	execute_subshell(t_env *env, t_ast **ast, int *lfds)
{
	t_ast	*left;

	left = (*ast)->left;
	ast_remove(ast);
	exec_subtree(env, &left, NULL, lfds);
	if (forked(false))
		closeall(lfds);
	ast_clear(&left);
}
