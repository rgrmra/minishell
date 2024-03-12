/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_config_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:58:32 by rde-mour          #+#    #+#             */
/*   Updated: 2024/02/27 21:59:33 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_build_config(t_format **conf, int nb)
{
	(*conf)-> c = ' ';
	if ((*conf)-> flags & FLAG_LEFT)
		(*conf)-> flags &= ~FLAG_ZERO;
	if ((*conf)-> precision >= 0)
		(*conf)-> flags &= ~FLAG_ZERO;
	if ((*conf)-> flags & FLAG_ZERO)
		(*conf)-> c = '0';
	(*conf)-> sign = 0;
	if (nb < 0)
		(*conf)-> sign = '-';
	else if ((*conf) && (*conf)-> flags & FLAG_PLUS && nb > -1)
		(*conf)-> sign = '+';
	else if ((*conf)-> flags & FLAG_SPACE)
		(*conf)-> sign = ' ';
	if ((*conf)-> sign)
		(*conf)-> width--;
}
