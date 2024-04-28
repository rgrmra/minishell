/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:14:49 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 20:19:05 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"
#include <unistd.h>

void	builtin_echo(char **cmd)
{
	int i;

	i = 1;
	while (cmd[i])
		ft_putstr_fd(cmd[i++], STDIN_FILENO);
	ft_freesplit(cmd);
}
