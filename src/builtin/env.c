/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:09:37 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/19 15:47:46 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "execution.h"
#include "expansions.h"
#include "get_env.h"
#include <signal.h>

extern volatile sig_atomic_t	g_status;

void	builtin_env(t_env *env, char **args)
{
	g_status = 0;
	if (args[1])
		panic(*args, args[1], "doesn't accept arguments or flags", 1);
	else
		envprint(&env->vars);
}
