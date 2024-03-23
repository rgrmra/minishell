/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:08:52 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/22 19:34:09 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_string.h"
#include "expansions.h"
#include "get_env.h"
#include "tokenizer.h"
#include "strjoinsep.h"
#include <stdlib.h>

static char	*expand(char *begin, char *var, char *end)
{
	char	*tmp;
	char	*string;

	string = NULL;
	if (begin && var)
		string = ft_strjoin(begin, var);
	if (begin)
		free(begin);
	tmp = string;
	if (tmp && end)
		string = ft_strjoin(tmp, end);
	if (end)
		free(end);
	if (tmp)
		free(tmp);
	return (string);
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
		tmp2 = NULL;
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

static char	*check_expansion(t_env *env, char *word)
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
	tmp = expand(ft_substr(word, 0, start - 1), value,
			ft_substr(word, end, ft_strlen(&(*(word + end)))));
	free(value);
	return (tmp);
}

static void	resolve_quote(char *string)
{
	int		i;
	char	quote;

	if (!string)
		return ;
	i = 0;
	quote = '\0';
	while (*(string + i))
	{
		if (quote && string[i] == quote)
			quote = '\0';
		else if (!quote && ft_strchr("\'\"", string[i]))
			quote = string[i];
		else if (quote == '\'' && string[i] == '$')
			string[i] = 0x1A;
		else if (quote == '\'' && string[i] == 0x1A)
			string[i] = '$';
		i++;
	}
}

void	var_expansions(t_env *env, t_content *content)
{
	size_t	i;
	char	*str;

	if (!env || !content)
		return ;
	i = 0;
	str = content->string;
	resolve_quote(str);
	while (str && str[i] != '\0')
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			str = check_expansion(env, str);
			free(content->string);
			content->string = str;
		}
		else
			i++;
	}
	resolve_quote(str);
}
