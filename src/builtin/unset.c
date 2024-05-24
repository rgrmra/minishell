/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:09:03 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/22 07:34:18 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ft_ctype.h"
#include "get_env.h"
#include "execution.h"
#include "expansions.h"
#include "types.h"
#include <signal.h>
#include <stdlib.h>

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

int	check_flags(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		if (cmd[i][0] == '-' && cmd[i][1])
		{
			panic(*cmd, cmd[i], "doesn't accept options", EXIT_FAILURE);
			g_status = EXIT_FAILURE;
			return (true);
		}
	}
	return (false);
}

void	builtin_unset(t_env *env, char **cmd)
{
	int	i;

	g_status = EXIT_SUCCESS;
	if (check_flags(cmd))
		return ;
	i = 0;
	while (cmd[++i])
	{
		if (!check_args(cmd[i]))
		{
			panic(*cmd, cmd[i], "not a valid identifier", EXIT_FAILURE);
			g_status = EXIT_FAILURE;
		}
		else
			envdel(&env->vars, cmd[i]);
	}
}
