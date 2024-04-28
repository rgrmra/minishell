/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:06:38 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 19:16:51 by rde-mour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "ft_stdlib.h"
#include "types.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

int	*alloc_fds(void)
{
	int	*fds;

	fds = (int *)ft_calloc(4, sizeof(int));
	fds[2] = -2;
	fds[3] = -2;
	return (fds);
}

int	forked(int status)
{
	static int	isforked;

	if (status == true)
		isforked = true;
	if (isforked)
		rl_clear_history();
	return (isforked);
}

void	closeall(int *fds)
{
	if (fds)
	{
		if (fds[0] > -1)
			close(fds[0]);
		if (fds[1] > -1)
			close(fds[1]);
		if (fds[2] > -1)
			close(fds[2]);
		if (fds[3] > -1)
			close(fds[3]);
		free(fds);
	}
	if (forked(false))
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
}

void	execute(t_env *env, t_ast **ast, int *fds)
{
	if (!ast || !(*ast))
		return ;
	if ((*ast)->content->type & COMMAND)
		execute_command(env, ast, fds);
	else if ((*ast)->content->type & (LESS | DLESS | GREATER | DGREATER))
		execute_redirection(env, ast, fds);
	else if ((*ast)->content->type & VBAR)
		execute_pipe(env, ast, fds);
	else if ((*ast)->content->type & (AND | OR))
		execute_condition(env, ast, fds);
	else if ((*ast)->content->type & PAREN)
		execute_subshell(env, ast, fds);
}
