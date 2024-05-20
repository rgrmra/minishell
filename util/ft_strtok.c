/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:28:18 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/19 23:22:49 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdio.h>
#include <stdlib.h>

static char	check_sub(char *input, ssize_t i, ssize_t *sub)
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

static char	check_quote(char quote, char *input, ssize_t i)
{
	static ssize_t	sub;

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

static size_t	count_words(char *str, char c)
{
	size_t	i;
	size_t	words;
	char	quote;

	if (!str)
		return (0);
	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			words++;
		quote = 0;
		while (str[i] && (quote || str[i] != c))
			quote = check_quote(quote, str, i++);
	}
	return (words);
}

static char	*find_word(const char **str, char c)
{
	int		i[2];
	char	*string;
	char	*word;
	char	quote;

	i[0] = 0;
	string = (char *) *str;
	while (string[i[0]] && string[i[0]] == c)
		i[0]++;
	quote = 0;
	i[1] = i[0];
	while (string[i[1]] && (quote || string[i[1]] != c))
		quote = check_quote(quote, string, i[1]++);
	word = ft_substr(string, i[0], i[1] - i[0]);
	while (i[1]--)
		(*str)++;
	return (word);
}

char	**ft_strtok(const char *str, char c)
{
	size_t	i;
	size_t	words;
	char	**new;

	words = count_words((char *) str, c);
	new = (char **) malloc(sizeof(char *) * (words + 2));
	if (!new)
		return (0);
	i = 0;
	if (!words)
		new[i++] = ft_strdup("");
	while (words--)
	{
		*(new + i) = find_word(&str, c);
		if (!(*(new + i++)))
		{
			i = 0;
			while (*(new + i))
				free(*(new + i++));
			free(new);
			return (0);
		}
	}
	new[i] = NULL;
	return (new);
}

//#include <stdio.h>
//int	main(int argc, char **argv)
//{
//	int	i;
//	char **str = ft_strtok(argv[1], ' ');
//
//	i = 0;
//	while (str[i])
//	{
//		printf("%s\n", str[i]);
//		free(str[i++]);
//	}
//	free(str);
//}
