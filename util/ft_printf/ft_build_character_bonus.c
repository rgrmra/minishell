/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_character_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:25:07 by rde-mour          #+#    #+#             */
/*   Updated: 2024/02/27 21:59:02 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_build_character(t_node **list, int character, t_format *conf)
{
	conf -> flags &= ~FLAG_PLUS;
	conf -> flags &= ~FLAG_SPACE;
	conf -> flags &= ~FLAG_HASH;
	conf -> flags &= ~FLAG_ZERO;
	conf -> precision = -1;
	conf -> characters = 0;
	ft_build_config(&conf, 0);
	lstadd_front(&(conf -> characters), lstnew(character));
	ft_build(list, conf);
}
