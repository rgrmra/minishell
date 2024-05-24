/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansions_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:32:28 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/22 06:50:48 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "types.h"
#include "ft_string.h"

static int	check(char *str)
{
	if (*str)
		return (-1);
	return (0);
}

static int	inner_wildcard(char *pattern, char *str)
{
	int	rest;

	if (*pattern)
		rest = wildcard(pattern, str);
	else if (*str)
		rest = -1;
	else
		rest = 0;
	return (rest);
}

int	wildcard(char *pattern, char *str)
{
	int		rest;
	char	*here;

	while (*pattern)
	{
		if (*pattern == '*')
		{
			here = str;
			while (*str)
				str++;
			while (str != here)
			{
				rest = inner_wildcard(pattern, str);
				if (!rest)
					return (0);
				else if (rest < 0)
					return (1);
				--str;
			}
		}
		else if (*str++ != *pattern)
			return (1);
		pattern++;
	}
	return (check(str));
}

int	check_wildcard(char *cmd)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (cmd[i])
	{
		if (!quote && ft_strchr("\'\"", cmd[i]))
			quote = cmd[i];
		else if (quote && cmd[i] == quote)
			quote = '\0';
		if (!quote && cmd[i] == '*')
			return (true);
		i++;
	}
	return (false);
}

int	has_wildcard(char **cmd)
{
	int		count;
	int		size;

	size = 0;
	count = 0;
	while (cmd[size])
	{
		if (check_wildcard(cmd[size]))
			count++;
		size++;
	}
	return (count);
}
