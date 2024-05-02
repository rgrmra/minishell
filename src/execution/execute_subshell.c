/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:50:33 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/01 22:17:27 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "execution.h"
#include "get_env.h"
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
		rl_clear_history();
		ast_clear(clear);
		execute(env, ast, lfds);
		envclear(&(env->vars));
		ft_hshfree(env->builtins);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
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
	closeall(lfds);
	ast_clear(&left);
}
