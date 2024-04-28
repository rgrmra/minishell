/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:49:21 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 18:37:31 by rde-mour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "builtin.h"
#include "execution.h"
#include "expansions.h"
#include "ft_string.h"
#include "get_env.h"
#include "types.h"
#include <stdlib.h>

int	builtin_exit(t_env *env, t_ast **ast, char **cmd, int *fds)
{
	if (ft_strncmp(*cmd, "exit", 5) != 0)
		return (false);
	ast_clear(ast);
	envclear(&(env->vars));
	closeall(fds);
	ft_freesplit(cmd);
	exit(EXIT_SUCCESS);
	return (true);
}
