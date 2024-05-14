/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:08:52 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/13 21:15:24 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "ft_ctype.h"
#include "ft_string.h"
#include "get_env.h"
#include "tokenizer.h"
#include "utils.h"
#include <stdlib.h>

static char	*expand(char *begin, char *var, char *end)
{
	char	*tmp;
	char	*literal;

	literal = NULL;
	if (begin && var)
		literal = ft_strjoin(begin, var);
	if (begin)
		free(begin);
	tmp = literal;
	if (tmp && end)
		literal = ft_strjoin(tmp, end);
	if (end)
		free(end);
	if (tmp)
		free(tmp);
	return (literal);
}

static char	*var_to_string(t_var *var)
{
	char	**splitted;
	char	*tmp;
	char	*tmp2;

	if (!var)
		return (ft_strdup(""));
	tmp = NULL;
	splitted = var->values;
	while (*splitted)
	{
		tmp2 = ft_strdup("");
		if (!tmp)
			tmp = ft_strdup(*(splitted)++);
		else
			tmp2 = strjoinsep(tmp, *(splitted)++, ':');
		if (tmp2)
		{
			free(tmp);
			tmp = ft_strdup(tmp2);
			free(tmp2);
		}
	}
	return (tmp);
}

char	*check_expansion(t_env *env, char *word)
{
	int		start;
	int		end;
	char	*tmp;
	char	*value;

	if (!env)
		return (ft_strdup(""));
	start = 0;
	while (!ft_strchr("$\0", *(word + start)))
		start++;
	end = ++start;
	while (ft_isalnum(*(word + end)) || *(word + end) == '_')
		end++;
	tmp = ft_substr(word, start, end - start);
	value = var_to_string(envget(&(env->vars), tmp));
	free(tmp);
	tmp = expand(ft_substr(word, 0, start - 1), value, ft_substr(word, end,
				ft_strlen(&(*(word + end)))));
	free(value);
	return (tmp);
}

//static void	resolve_quote(char *literal)
//{
//	int		i;
//	char	quote;
//
//	if (!literal)
//		return ;
//	i = 0;
//	quote = '\0';
//	while (*(literal + i))
//	{
//		if (quote && literal[i] == quote)
//			quote = '\0';
//		else if (!quote && ft_strchr("\'\"", literal[i]))
//			quote = literal[i];
//		else if (quote == '\'' && literal[i] == '$')
//			literal[i] = 0x1A;
//		else if (quote == '\'' && literal[i] == 0x1A)
//			literal[i] = '$';
//		i++;
//	}
//}

void	var_expansions(t_env *env, t_token *content)
{
	size_t	i;
	char	*str;

	if (!env || !content)
		return ;
	i = 0;
	str = content->literal;
	//resolve_quote(str);
	while (str && str[i] != '\0')
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'
			|| str[i + 1] == '?'))
		{
			str = check_expansion(env, str);
			free(content->literal);
			content->literal = str;
		}
		else
			i++;
	}
	//resolve_quote(str);
}
