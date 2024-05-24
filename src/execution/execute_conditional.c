/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_conditional.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:43:52 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/19 15:49:43 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

void	execute_conditional(t_env *env, t_ast *ast)
{
	int		token;

	token = ast->content->type;
	execute(env, ast->left);
	if ((g_status > 0 && token & AND) || (g_status == 0 && token & OR))
		return ;
	execute(env, ast->right);
}
