/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:49:21 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/19 23:20:47 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "types.h"
#include "ft_stdlib.h"
#include "ft_ctype.h"
#include "ft_stdio.h"
#include "builtin.h"
#include "ft_string.h"
#include "expansions.h"
#include "execution.h"
#include <signal.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

static int	check_arg(char *arg)
{
	int	i;

	if (!arg)
		return (true);
	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (ft_isdigit(arg[i]))
		i++;
	if (arg[i])
		return (false);
	return (true);
}

void	builtin_exit(t_env *env, char **args)
{
	int	i;

	i = 0;
	rl_clear_history();
	while (args[++i])
	{
		if (check_arg(args[i]))
		{
			g_status = ft_atoi(args[i]);
			break ;
		}
	}
	ft_putendl_fd(*args, 2);
	if (i > 1 && args[1] && !check_arg(args[1]))
	{
		printf("%s: %s: numeric argument required", *args, args[i]);
		g_status = 2;
		//panic(*args, args[i], "numeric argument required", 2);
	}
	else if (args[1] && args[2])
	{
		panic(*args, NULL, "too many arguments", 1);
		return ;
	}
	ft_freesplit(args);
	clearall(env);
}
