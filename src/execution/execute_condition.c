/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_condition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:43:52 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/30 18:50:18 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

void	execute_condition(t_env *env, t_ast **ast, int *fds, int *std)
{
	int		token;
	t_ast	*left;
	t_ast	*right;

	free(fds);
	token = (*ast)->content->type;
	left = (*ast)->left;
	right = (*ast)->right;
	ast_remove(ast);
	execute(env, &left, NULL, std);
	if ((g_status == 0 && token & AND) || (g_status > 0 && token & OR))
		execute(env, &right, NULL, std);
	ast_clear(&left);
	ast_clear(&right);
}
