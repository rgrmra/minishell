/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:54:38 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/03 21:00:11 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "tokenizer.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

static t_ast	*invalid_fd(t_ast *ast)
{
	if (!ast)
		return (NULL);
	g_status = 1;
	return (NULL);
}

static void	open_file(t_ast *ast, int *to_open, int *to_check, mode_t flags)
{
	static const mode_t	mode = S_IRUSR | S_IWUSR;

	if (*to_open > -1)
	{
		close(*to_open);
		*to_open = -2;
	}
	if (*to_open != -1 && *to_check != -1)
	{
		*to_open = open(ast->right->content->literal, flags, mode);
		if (*to_open == -1)
			printf("minishell: %s: %s\n", ast->right->content->literal, strerror(errno));
		if (ast->content->type & DLESS)
			unlink(ast->content->literal);
	}
}

t_ast	*redirection(t_env *env, t_ast *ast, int *fdin, int *fdout)
{
	t_ast	*tmp;

	if (!ast)
		return (NULL);
	tmp = NULL;
	if (ast && ast->left && ast->left->content->type & COMMAND)
		tmp = ast->left;
	else if (ast && ast->left
		&& ast->left->content->type & (LESS | DLESS | GREATER | DGREATER))
		tmp = redirection(env, ast->left, fdin, fdout);
	if (ast && ast->content->type & (LESS | DLESS))
		open_file(ast, fdout, fdin, O_RDONLY);
	if (ast && ast->content->type & GREATER)
		open_file(ast, fdin, fdout, O_CREAT | O_TRUNC | O_WRONLY);
	else if (ast && ast->content->type & DGREATER)
		open_file(ast, fdin, fdout, O_CREAT | O_APPEND | O_WRONLY);
	if (*fdout == -1 || *fdin == -1)
		return (invalid_fd(ast));
	if (*fdin > -1)
		dup2(*fdin, STDOUT_FILENO);
	if (*fdout > -1)
		dup2(*fdout, STDIN_FILENO);
	return (tmp);
}

void	execute_redirection(t_env *env, t_ast *ast, int *lfds)
{
	int		*fds;
	t_ast	*tmp;

	fds = alloc_fds();
	env->stds[0] = dup(STDIN_FILENO);
	env->stds[1] = dup(STDOUT_FILENO);
	pipe(fds);
	tmp = redirection(env, ast, &fds[2], &fds[3]);
	closeall(lfds);
	if (!tmp || fds[2] == -1 || fds[3] == -1)
		closeall(fds);
	else if (tmp && fds[2] != -1 && fds[3] != -1)
		execute(env, tmp, fds);
	dup2(env->stds[0], STDIN_FILENO);
	dup2(env->stds[1], STDOUT_FILENO);
	close(env->stds[0]);
	close(env->stds[1]);
}
