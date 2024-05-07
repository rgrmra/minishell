/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:14:49 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/06 21:09:30 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"
#include "types.h"
#include <unistd.h>

void	builtin_echo(t_env *env, char **cmd)
{
	int	i;
	int	end;

	(void)env;
	i = 1;
	end = false;
	if (cmd[1] && ft_strncmp(cmd[1], "-n", 3) == 0)
		end = true;
	while (cmd[i + end])
	{
		if (i > 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(cmd[i++ + end], STDOUT_FILENO);
	}
	if (!end)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
