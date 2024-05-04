/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:06:38 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/04 12:48:24 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "get_env.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

void	set_fds(int *fds)
{
	fds[2] = -2;
	fds[3] = -2;
	fds[4] = -2;
	fds[5] = -2;
}

void	closeall(int *fds)
{
	if (!fds)
		return ;
	if (fds[0] > -1)
		close(fds[0]);
	if (fds[1] > -1)
		close(fds[1]);
	if (fds[2] > -1)
		close(fds[2]);
	if (fds[3] > -1)
		close(fds[3]);
}

void	execute(t_env *env, t_ast *ast, int *fds)
{
	if (!ast)
		return ;
	if (ast->content->type & COMMAND)
		execute_command(env, ast, fds);
	else if (ast->content->type & (LESS | DLESS | GREATER | DGREATER))
		execute_redirection(env, ast);
	else if (ast->content->type & VBAR)
		execute_pipe(env, ast);
	else if (ast->content->type & (AND | OR))
		execute_conditional(env, ast);
	else if (ast->content->type & PAREN)
		execute_subshell(env, ast);
}

void	clearall(t_env *env)
{
	ast_clear(env->ast);
	envclear(&(env->vars));
	ft_hshfree(env->builtins);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(g_status);
}
