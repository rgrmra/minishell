/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:49:21 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/30 19:11:11 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ft_string.h"
#include <stdlib.h>

void	builtin_exit(char **args)
{
	if (args)
		ft_freesplit(args);
	exit(EXIT_SUCCESS);
}
