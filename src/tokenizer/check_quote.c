/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:09:37 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/11 20:23:21 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdio.h>
#include <signal.h>

extern volatile	sig_atomic_t	g_status;

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

int	find_quote(char *tmp)
{
	int		i;
	char	quote;

	if (!tmp || !(*tmp))
		return (1);
	i = 0;
	quote = '\0';
	while (tmp && tmp[i])
	{
		quote = check_quote(quote, tmp, i);
		if (!quote && ft_strchr(" \t", tmp[i]))
			tmp[i] = ' ';
		i++;
	}
	if (!quote)
		return (1);
	printf("%s %c\n", "unclosed parser error", quote);
	g_status = 2;
	return (0);
}
