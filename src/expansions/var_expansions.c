/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:08:52 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/19 15:47:11 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "ft_ctype.h"
#include "ft_string.h"
#include "get_env.h"
#include "ft_stdlib.h"
#include "tokenizer.h"
#include "utils.h"
#include <signal.h>
#include <stdlib.h>

extern volatile sig_atomic_t	g_status;

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
	if (!literal)
		literal = ft_strdup("");
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
		if (!tmp)
			tmp = ft_strdup(*(splitted)++);
		else
		{
			tmp2 = strjoinsep(tmp, *(splitted)++, ':');
			free(tmp);
			tmp = tmp2;
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

	value = NULL;
	start = 0;
	while (!ft_strchr("$\0", *(word + start)))
		start++;
	end = ++start;
	if (*(word + start) != '?')
	{
		while (ft_isalnum(*(word + end)) || *(word + end) == '_')
			end++;
		tmp = ft_substr(word, start, end - start);
		value = var_to_string(envget(&env->vars, tmp));
		free(tmp);
	}
	else if (end++)
		value = ft_itoa(g_status);
	tmp = expand(ft_substr(word, 0, start - 1), value, ft_substr(word, end,
				ft_strlen(&(*(word + end)))));
	free(value);
	return (tmp);
}

static char	check_quote(char quote, char *input, int i)
{
	if (quote && (input[i] == quote))
		return ('\0');
	else if (!quote && ft_strchr("\"\'", input[i]))
		return (input[i]);
	return (quote);
}

void	var_expansions(t_env *env, t_token *content)
{
	size_t	i;
	char	*str;
	char	quote;

	if (!env || !content)
		return ;
	i = 0;
	str = content->literal;
	quote = 0;
	while (str && str[i] != '\0')
	{
		quote = check_quote(quote, str, i);
		if (quote != '\'' && str[i] == '$' && (ft_isalpha(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?'))
		{
			str = check_expansion(env, str);
			free(content->literal);
			content->literal = str;
		}
		else
			i++;
	}
}
