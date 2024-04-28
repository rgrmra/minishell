/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:49:21 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/24 20:24:35 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "expansions.h"
#include "ft_stdio.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "ft_ctype.h"
#include "get_env.h"
#include "unistd.h"
#include "builtin.h"
#include <stdlib.h>
#include "types.h"

int	builtin_exit(t_env *env, t_ast **ast, char **cmd, int *fds)
{
	if (ft_strncmp(*cmd, "exit", 5) != 0)
		return (false);
	ast_clear(ast);
	envclear(&(env->vars));
	closeall(fds);
	ft_memclear((void **) cmd, &free);
	exit(EXIT_SUCCESS);
	return (true);
}
