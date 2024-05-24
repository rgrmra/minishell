/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:11:06 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/24 13:09:56 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "ft_string.h"
#include "utils.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

extern volatile sig_atomic_t	g_status;

static char	check_quote(char quote, char *input, int i)
{
	if (quote && (input[i] == quote))
		return ('\0');
	else if (!quote && ft_strchr("\"\'", input[i]))
		return (input[i]);
	return (quote);
}

static char	*expand_input(char *tmp, char *input)
{
	size_t	i;
	size_t	j;
	char	quote;

	i = -1;
	j = 0;
	quote = 0;
	while (input[++i])
	{
		quote = check_quote(quote, input, i);
		if (!quote && ft_strchr(";|<>&", input[i]))
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

	input = *str;
	if (!input || !(*input))
		return (NULL);
	tmp = (char *) malloc(ft_strlen(input) * 3 * sizeof(char));
	if (!tmp)
		exit_error("malloc", MALLOC_FAILURE);
	tmp = expand_input(tmp, input);
	splitted = ft_strtok(tmp, ' ');
	free(tmp);
	free(input);
	return (splitted);
}
