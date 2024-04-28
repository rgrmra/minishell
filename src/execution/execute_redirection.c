/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:54:38 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 18:37:43 by rde-mour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "get_env.h"
#include "types.h"
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

t_ast	*redirection(t_env *env, t_ast **ast, int *fdin, int *fdout)
{
	t_ast	*tmp;

	if (!ast || !(*ast))
		return (NULL);
	tmp = NULL;
	if ((*ast)->left && (*ast)->left->content->type & COMMAND)
		tmp = ((*ast)->left);
	else if ((*ast)->left
		&& (*ast)->left->content->type & (LESS | DLESS | GREATER | DGREATER))
		tmp = redirection(env, &((*ast)->left), fdin, fdout);
	if ((*ast)->content->type & (LESS | DLESS))
	{
		if (*fdout > -1)
			close(*fdout);
		*fdout = open((*ast)->right->content->literal, O_RDONLY, 0644);
		ast_remove(&((*ast)->right));
	}
	if ((*ast)->content->type & GREATER)
	{
		if (*fdin > -1)
			close(*fdin);
		*fdin = open((*ast)->right->content->literal,
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
		ast_remove(&((*ast)->right));
	}
	else if ((*ast)->content->type & DGREATER)
	{
		if (*fdin > -1)
			close(*fdin);
		*fdin = open((*ast)->right->content->literal,
				O_CREAT | O_APPEND | O_WRONLY, 0644);
		ast_remove(&((*ast)->right));
	}
	ast_remove(ast);
	if (*fdout == -1 || *fdin == -1)
	{
#include <stdio.h>
		printf("no such file\n");
		exit(EXIT_FAILURE);
	}
	if (*fdout > -1)
		dup2(*fdout, STDIN_FILENO);
	return (tmp);
}

void	execute_redirection(t_env *env, t_ast **ast, int *lfds)
{
	pid_t	pid;
	int		*fds;
	t_ast	*tmp;
	int		status;

	status = 0;
	if (!ast || !(*ast))
		return ;
	fds = alloc_fds();
	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		forked(true);
		tmp = redirection(env, ast, &fds[2], &fds[3]);
		if (!tmp)
			closeall(fds);
		execute(env, &tmp, fds);
		closeall(lfds);
		envclear(&(env->vars));
		exit(g_status);
	}
	closeall(fds);
	closeall(lfds);
	waitpid(pid, &status, WUNTRACED);
	ast_clear(ast);
	g_status = WEXITSTATUS(status);
}
