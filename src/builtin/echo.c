/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:14:49 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/29 20:37:30 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"
#include "types.h"
#include <unistd.h>

void	builtin_echo(char **cmd, int *fds)
{
	int	i;
	int	end;
	int	fd;

	fd = STDOUT_FILENO;
	if (fds && fds[2] >= 0)
		fd = fds[2];
	i = 1;
	end = false;
	if (cmd[1] && ft_strncmp(cmd[1], "-n", 3) == 0)
		end = true;
	while (cmd[i + end])
	{
		if (i > 1)
			ft_putchar_fd(' ', fd);
		ft_putstr_fd(cmd[i++ + end], fd);
	}
	if (!end)
		ft_putchar_fd('\n', fd);
	ft_freesplit(cmd);
}
