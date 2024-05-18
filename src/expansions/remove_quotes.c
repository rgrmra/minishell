/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:47:00 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/17 22:02:13 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	remove_quotes_aux(char *word)
{
	int		i;
	int		quote;
	char	sign;

	i = 0;
	quote = 0;
	sign = '\0';
	while (word && word[i])
	{
		if (sign != '\0' && quote == 2)
		{
			quote = 0;
			sign = '\0';
		}
		if (sign == '\0' && quote == 0 && ft_strchr("\'\"", word[i]))
			sign = word[i];
		if (sign != '\0' && word[i] == sign && quote++ < 2)
		{
			ft_strlcpy(&word[i], &word[i + 1], ft_strlen(word) - 1);
			i--;
		}
		i++;
	}
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
