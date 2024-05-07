/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:09:03 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/05 21:08:07 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ft_ctype.h"
#include "get_env.h"
#include "execution.h"
#include "expansions.h"
#include "types.h"
#include <signal.h>

extern volatile sig_atomic_t	g_status;

static int	check_args(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[i]) || arg[i] == '_')
		i++;
	else
		return (false);
	while (ft_isalnum(arg[i]))
		i++;
	if (!arg)
		return (false);
	return (true);
}

int	check_flags(char **args)
{
	int	i;

	i = 0;
	g_status = 0;
	while (args[++i])
	{
		if (args[i][0] == '-' && args[i][1])
		{
			panic(*args, args[i], "doesn't accept options", 1);
			g_status = 1;
			return (true);
		}
	}
	return (false);
}

void	builtin_unset(t_env *env, char **args)
{
	int	i;

	g_status = 0;
	if (check_flags(args))
		return ;
	i = 0;
	while (args[++i])
	{
		if (!check_args(args[i]))
		{
			panic(*args, args[i], "not a valid identifier", 1);
			g_status = 1;
		}
		else
			envdel(&env->vars, args[i]);
	}
}
