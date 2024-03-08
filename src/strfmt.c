/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strfmt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:11:06 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/08 19:48:07 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ctype.h"
#include "ft_string.h"

static char	*find_quote(char *tmp)
{
	int		i;
	char	sign;

	i = 0;
	sign = 0;
	while (tmp && *(tmp + i))
	{
		if (sign && *(tmp + i) == sign)
			sign = 0;
		else if (!sign && (*(tmp + i) == '\"' || *(tmp + i) == '\''))
			sign = *(tmp + i);
		else if (!sign && ft_isspace(*(tmp + i)))
			*(tmp + i) = ' ';
		else if (sign && *(tmp + i) == ' ')
			*(tmp + i) = 0x1A;
		i++;
	}
	return (tmp);
}

static char	*expand_input(char *tmp, char *input)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*(input + i))
	{
		if (ft_strchr("&|<>;", *(input + i)))
		{
			if (i && *(input + i - 1) != *(input + i))
				*(tmp + j++) = ' ';
			*(tmp + j++) = *(input + i);
			if (*(input + i + 1) && *(input + i + 1) != *(input + i))
				*(tmp + j++) = ' ';
		}
		else
			*(tmp + j++) = *(input + i);
		i++;
	}
	*(tmp + i) = '\0';
	free(input);
	return (tmp);
}

static void	strrplc(char *str, char old, char new)
{
	size_t	i;

	if (!str)
		return ;
	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == old)
			*(str + i) = new;
		i++;
	}
}

char	**format_input(char *input)
{
	char	**splitted;
	char	*tmp;
	size_t	size;
	int		i;

	splitted = 0;
	if (!input || !(*input))
		return (splitted);
	size = ft_strlen(input);
	input = find_quote(ft_strdup(input));
	tmp = (char *) malloc(size * 2 * sizeof(char));
	if (!tmp)
		return (splitted);
	tmp = expand_input(tmp, input);
	splitted = ft_split(tmp, ' ');
	free(tmp);
	i = 0;
	while (*(splitted + i))
		strrplc(*(splitted + i++), 0x1A, ' ');
	return (splitted);
}
