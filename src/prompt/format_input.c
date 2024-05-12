/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:11:06 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/11 11:22:13 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "utils.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

extern volatile sig_atomic_t	g_status;

static char	*expand_input(char *tmp, char *input)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (input[++i])
	{
		if (ft_strchr("|<>&", input[i]))
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
	tmp = (char *)malloc(ft_strlen(input) * 3 * sizeof(char));
	if (!tmp)
		return (NULL);
	tmp = expand_input(tmp, input);
	splitted = ft_strtok(tmp, ' ');
	free(tmp);
	free(input);
	return (splitted);
}
