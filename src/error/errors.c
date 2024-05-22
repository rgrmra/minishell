/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 06:36:05 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/22 06:41:30 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "ft_stdio.h"
#include <stdlib.h>
#include <unistd.h>

void	exit_error(char *message, int status)
{
	ft_putstr_fd("minishell: failed to:", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	exit(status);
}
