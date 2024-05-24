/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:09:37 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/22 07:19:16 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "execution.h"
#include "expansions.h"
#include "get_env.h"
#include <signal.h>
#include <stdlib.h>

extern volatile sig_atomic_t	g_status;

void	builtin_env(t_env *env, char **cmd)
{
	g_status = EXIT_SUCCESS;
	if (cmd[1])
		panic(*cmd, cmd[1], "doesn't accept arguments or flags", EXIT_FAILURE);
	else
		envprint(&env->vars);
}
