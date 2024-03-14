/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:08:52 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/14 09:18:53 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linkedlist.h"
#include "ft_string.h"
#include "expansions.h"
#include "get_env.h"
#include "tokens.h"
#include "ft_printf_bonus.h"
#include <stdlib.h>

static void	remove_quotes(char *word, size_t size)
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
		if (sign != '\0' && quote < 2 && word[i] == sign)
		{
			quote++;
			ft_strlcpy(&word[i], &word[i + 1], size--);
			i--;
		}
		i++;
	}
}

static char	*expand(char *begin, char *var, char *end)
{
	char	*tmp;
	char	*string;

	string = ft_strjoin(begin, var);
	free(begin);
	tmp = string;
	string = ft_strjoin(tmp, end);
	free(end);
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
			ft_sprintf(&tmp2, "%s:%s", tmp, *(splitted)++);
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
	while (!ft_strchr(" $\t\"\'\0", *(word + end)))
		end++;
	tmp = ft_substr(word, start, end - start);
	value = var_to_string(envget(&(env->envp), tmp));
	if (!(*value))
	{
		free(value);
		value = var_to_string(envget(&(env->exports), tmp));
	}
	free(tmp);
	tmp = expand(ft_substr(word, 0, start - 1), value,
			ft_substr(word, end, ft_strlen(&(*(word + end)))));
	free(value);
	return (tmp);
}

void	var_expansions(t_env *env, t_list **tokens)
{
	char		*string;
	t_list		*tmp;
	t_content	*content;

	if (!env || !tokens)
		return ;
	tmp = *tokens;
	while (tmp)
	{
		content = (t_content *) tmp->content;
		while (*(content->string) != '\'' && ft_strchr(content->string, '$'))
		{
			string = check_expansion(env, content->string);
			free(content->string);
			content->string = string;
		}
		remove_quotes(content->string, ft_strlen(content->string));
		tmp = tmp->next;
	}
}
