/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrplc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:56:34 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 19:17:21 by rde-mour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	strrplc(char *str, char old, char new)
{
	size_t	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == old)
			str[i] = new;
		i++;
	}
}
