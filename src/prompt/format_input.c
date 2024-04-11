/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:11:06 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/08 16:34:25 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "ft_string.h"
#include "utils.h"

static char	check_quote(char quote, char *input, int i)
{
	static int	sub;

	if (i == 0)
		sub = 0;
	if (!quote || ft_strchr("()", quote))
	{
		if (input[i] == ')')
			sub--;
		else if (input[i] == '(')
			sub++;
		if (sub > 0)
			return ('(');
		else if (sub < 0)
			return (')');
		quote = '\0';
	}
	if (sub == 0 && quote && (input[i] == quote))
		return ('\0');
	else if (sub == 0 && !quote && ft_strchr("\'\"", input[i]))
		return (input[i]);
	return (quote);
}

static char	*find_quote(char *tmp)
{
	int		i;
	char	quote;

	if (!tmp || !(*tmp))
		return (tmp);
	i = 0;
	quote = '\0';
	while (tmp && tmp[i])
	{
		quote = check_quote(quote, tmp, i);
		if (!quote && ft_strchr(" \t", tmp[i]))
			tmp[i] = ' ';
		else if (quote && tmp[i] == ' ')
			tmp[i] = 0x1A;
		i++;
	}
	if (!quote)
		return (tmp);
	printf("%s %c\n", "unclosed quote parser error", quote);
	return (NULL);
}

static char	*expand_input(char *tmp, char *input)
{
	size_t	i;
	size_t	j;
	char	quote;

	i = 0;
	j = 0;
	quote = '\0';
	while (input[i])
	{
		if (ft_strchr("\"\'\0", quote) && input[i] == '(')
			tmp[j++] = ' ';
		quote = check_quote(quote, input, i);
		if (!quote && ft_strchr("|<>&", input[i]))
		{
			if (i && input[i - 1] != input[i])
				tmp[j++] = ' ';
			tmp[j++] = input[i];
			if (input[i + 1] != input[i])
				tmp[j++] = ' ';
		}
		else
			tmp[j++] = input[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	**format_input(char *input)
{
	char	**splitted;
	char	*tmp;
	int		i;

	input = find_quote(input);
	if (!input || !(*input))
		return (NULL);
	tmp = (char *) malloc(ft_strlen(input) * 3 * sizeof(char));
	if (!tmp)
		return (NULL);
	tmp = expand_input(tmp, input);
	splitted = ft_split(tmp, ' ');
	free(tmp);
	i = 0;
	while (splitted[i])
		strrplc(splitted[i++], 0x1A, ' ');
	return (splitted);
}
