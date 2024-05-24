/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:49:21 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/22 07:25:01 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "types.h"
#include "errors.h"
#include "ft_stdlib.h"
#include "ft_ctype.h"
#include "ft_stdio.h"
#include "builtin.h"
#include "ft_string.h"
#include "expansions.h"
#include "execution.h"
#include <signal.h>
#include <stdlib.h>
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

void	builtin_exit(t_env *env, char **cmd)
{
	int	i;

	i = 0;
	rl_clear_history();
	while (cmd[++i])
	{
		if (check_arg(cmd[i]))
		{
			g_status = ft_atoi(cmd[i]);
			break ;
		}
	}
	ft_putendl_fd(*cmd, STDERR_FILENO);
	if (i > 1 && cmd[1] && !check_arg(cmd[1]))
	{
		panic(*cmd, cmd[i], "numeric argument required", ARGUMENT_ERROR);
		g_status = 2;
	}
	else if (cmd[1] && cmd[2])
		return (panic(*cmd, NULL, "too many arguments", EXIT_FAILURE));
	ft_freesplit(cmd);
	clearall(env);
}
