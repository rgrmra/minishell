/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:11:06 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/04 12:21:35 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

static char	check_sub(char *input, int i, int *sub)
{
	static char	tmp;

	if (i == 0)
		tmp = '\0';
	if (*sub && !tmp && ft_strchr("\"\'", input[i]))
		tmp = input[i];
	else if (*sub && tmp && tmp == input[i])
		tmp = '\0';
	if (!tmp && input[i] == ')')
		(*sub)--;
	else if (!tmp && input[i] == '(')
		(*sub)++;
	if (*sub > 0)
		return ('(');
	else if (*sub < 0)
		return (')');
	return ('\0');
}

static char	check_quote(char quote, char *input, int i)
{
	static int	sub;

	if (i == 0)
		sub = 0;
	if (!quote || ft_strchr("()", quote))
		quote = check_sub(input, i, &sub);
	if (sub == 0 && quote && (input[i] == quote))
		return ('\0');
	else if (sub == 0 && !quote && ft_strchr("\'\"", input[i]))
		return (input[i]);
	return (quote);
}

char	*find_quote(char *tmp)
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

	i = -1;
	j = 0;
	quote = '\0';
	while (input[++i])
	{
		if (!ft_strchr("\"\'(", quote) && input[i] == '(')
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
	}
	tmp[j] = '\0';
	return (tmp);
}

char	**format_input(char **str)
{
	char	**splitted;
	char	*tmp;
	char	*input;
	int		i;

	input = *str;
	input = find_quote(input);
	if (!input || !(*input))
		return (NULL);
	tmp = (char *)malloc(ft_strlen(input) * 3 * sizeof(char));
	if (!tmp)
		return (NULL);
	tmp = expand_input(tmp, input);
	splitted = ft_split(tmp, ' ');
	free(tmp);
	free(input);
	i = 0;
	while (splitted[i])
		strrplc(splitted[i++], 0x1A, ' ');
	return (splitted);
}
