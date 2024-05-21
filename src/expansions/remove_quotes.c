/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:47:00 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/20 23:15:18 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "ft_string.h"

static void	copy(char *word)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] != -1)
			word[j++] = word[i];
		i++;
	}
	word[j] = '\0';
}

void	remove_quotes_aux(char *word)
{
	int	i;
	int	len;
	int	quote;

	i = 0;
	len = ft_strlen(word);
	quote = 0;
	while (word[i])
	{
		if (quote && quote == word[i])
		{
			quote = '\0';
			word[i] = -1;
		}
		else if (!quote && ft_strchr("\'\"", word[i]))
		{
			quote = word[i];
			word[i] = -1;
		}
		i++;
	}
	copy(word);
}

void	remove_quotes(char **word)
{
	int	i;

	if (!word || !(*word))
		return ;
	i = 0;
	while (word[i])
		remove_quotes_aux(word[i++]);
}
