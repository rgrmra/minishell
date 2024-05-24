/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_sep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:21:57 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/24 13:28:04 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "expansions.h"
#include "ast.h"

void	execute_sep(t_env *env, t_ast *ast)
{
	execute(env, ast->left);
	execute(env, ast->right);
}
