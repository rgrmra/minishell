/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:49:21 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/04 15:01:02 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "types.h"
#include "ft_stdlib.h"
#include "ft_ctype.h"
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
	int	status;

	rl_clear_history();
	i = 0;
	status = 0;
	while (args[i])
	{
		if (check_arg(args[i]))
		{
			status = ft_atoi(args[i]);
			break ;
		}
		i++;
	}
	if (status < 0)
		status = -status;
	g_status = status;
	if (i > 1 && args[1])
	{
		printf("minishell: exit: numeric argument required\n");
		g_status = 2;
	}
	else if (args[1] && args[2])
		printf("minishell: exit: too many arguments\n");
	ft_freesplit(args);
	clearall(env);
}
