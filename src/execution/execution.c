/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:06:38 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/22 18:43:09 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "errors.h"
#include "expansions.h"
#include "ft_hashmap.h"
#include "get_env.h"
#include "ft_stdlib.h"
#include <dirent.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

void	closefds(int *fds)
{
	if (!fds)
		return ;
	if (fds[0] > -1)
		close(fds[0]);
	if (fds[1] > -1)
		close(fds[1]);
}

void	execute(t_env *env, t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->content->type & COMMAND)
		execute_command(env, ast);
	else if (ast->content->type & (LESS | DLESS | GREATER | DGREATER))
		execute_redirection(env, ast);
	else if (ast->content->type & VBAR)
		execute_pipe(env, ast);
	else if (ast->content->type & (AND | OR))
		execute_conditional(env, ast);
	else if (ast->content->type & PAREN)
		execute_subshell(env, ast);
}

void	close_open_fds(void)
{
	struct dirent	*file;
	DIR				*root;
	int				fd;

	root = opendir("/proc/self/fd/");
	if (!root)
		exit_error("opendir", EXIT_FAILURE);
	while (1)
	{
		file = readdir(root);
		if (!file)
			break ;
		fd = ft_atoi(file->d_name);
		if (fd > -1 && fd < 1024)
			close(ft_atoi(file->d_name));
	}
	closedir(root);
}

void	clearall(t_env *env)
{
	close_open_fds();
	ast_clear(env->ast);
	envclear(&(env->vars));
	ft_hshfree(env->builtins);
	exit(g_status);
}
