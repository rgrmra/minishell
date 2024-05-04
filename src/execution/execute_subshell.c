/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:50:33 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/03 20:34:02 by rde-mour         ###   ########.org.br   */
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

static void	exec_subtree(t_env *env, t_ast *ast, int *lfds)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		rl_clear_history();
		execute(env, ast->left, lfds);
		ast_clear(env->ast);
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

void	execute_subshell(t_env *env, t_ast *ast, int *lfds)
{

	exec_subtree(env, ast, lfds);
	closeall(lfds);
}
