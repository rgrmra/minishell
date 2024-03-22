/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strfmt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:11:06 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/21 20:40:55 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "ft_ctype.h"
#include "ft_string.h"

static char	check_quote(char sign, char *input, int i)
{
	if (sign && (input[i] == sign))
		return ('\0');
	else if (!sign && ft_strchr("\'\"", input[i]))
		return (input[i]);
	return (sign);
}

static char	*find_quote(char *tmp)
{
	int		i;
	char	sign;

	i = 0;
	sign = '\0';
	while (tmp && tmp[i])
	{
		sign = check_quote(sign, tmp, i);
		if (!sign && ft_isspace(tmp[i]))
			tmp[i] = ' ';
		else if (sign && tmp[i] == ' ')
			tmp[i] = 0x1A;
		i++;
	}
	if (!sign)
		return (tmp);
	free(tmp);
	printf("%s %c\n", "unclosed quote parser error", sign);
	return (NULL);
}

static char	*expand_input(char *tmp, char *input)
{
	size_t	i;
	size_t	j;
	char	sign;

	i = 0;
	j = 0;
	sign = '\0';
	while (input[i])
	{
		sign = check_quote(sign, input, i);
		if (!sign && ft_strchr("()|<>&", input[i]) && input[i] != ' ')
		{
			if (i && (ft_strchr("()", input[i]) || input[i - 1] != input[i]))
				tmp[j++] = ' ';
			tmp[j++] = input[i];
			if (ft_strchr("()", input[i]) || input[i + 1] != input[i])
				tmp[j++] = ' ';
		}
		else
			tmp[j++] = input[i];
		i++;
	}
	tmp[j] = '\0';
	free(input);
	return (tmp);
}

static void	strrplc(char *str, char old, char new)
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

char	**format_input(char *input)
{
	char	**splitted;
	char	*tmp;
	size_t	size;
	int		i;

	splitted = NULL;
	if (!input || !(*input))
		return (splitted);
	size = ft_strlen(input) + 1;
	input = find_quote(ft_strdup(input));
	if (!input)
		return (splitted);
	tmp = (char *) malloc(size * 3 * sizeof(char));
	if (!tmp)
		return (splitted);
	tmp = expand_input(tmp, input);
	splitted = ft_split(tmp, ' ');
	free(tmp);
	i = 0;
	while (splitted[i])
		strrplc(splitted[i++], 0x1A, ' ');
	return (splitted);
}
