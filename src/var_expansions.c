/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:08:52 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/21 09:33:33 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_linkedlist.h"
#include "ft_string.h"
#include "expansions.h"
#include "get_env.h"
#include "tokens.h"
#include "strjoinsep.h"
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
	value = var_to_string(envget(&(env->envp), tmp));
	if (!value || !(*value))
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
	size_t		i;
	char		*string;
	t_list		*tmp;

	if (!env || !tokens)
		return ;
	tmp = *tokens;
	while (tmp)
	{
		i = 0;
		string = ((t_content *) tmp->content)->string;
		while (string && string[0] && string[i] != '\0')
		{
			if (string[i] == '$' && (ft_isalpha(string[i + 1])
					|| string[i + 1] == '_'))
			{
				string = check_expansion(env, string);
				free(((t_content *) tmp->content)->string);
				((t_content *) tmp->content)->string = string;
				i = 0;
			}
			else
				i++;
		}
		remove_quotes(string, ft_strlen(string));
		tmp = tmp->next;
	}
}
