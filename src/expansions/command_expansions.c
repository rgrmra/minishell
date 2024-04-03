/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:57:54 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/02 22:45:03 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "arraylist.h"
#include "expansions.h"
#include "ft_string.h"
#include "tokenizer.h"
#include "get_env.h"
#include "strjoinsep.h"

static char	*check_bultins(char *word)
{
	const char	*bultins[8] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit", NULL};
	size_t		i;

	if (!word)
		return (NULL);
	i = 0;
	while (*(bultins + i))
	{
		if (!ft_strncmp(word, *(bultins + i), ft_strlen(*(bultins + i)) + 1))
			return ((char *) *(bultins + i));
		i++;
	}
	return (NULL);
}

static char	*check_expansion(t_env *env, char *word)
{
	size_t	i;
	char	**paths;
	char	*path;
	t_var	*tmp;

	if (!env)
		return (ft_strdup(word));
	path = check_bultins(word);
	if (path)
		return (NULL);
	tmp = envget(&env->vars, "PATH");
	if (!tmp)
		return (ft_strdup(word));
	paths = tmp->values;
	if (!paths)
		return (ft_strdup(word));
	i = 0;
	while (paths[i])
	{
		path = strjoinsep(paths[i++], word, '/');
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
	}
	return (ft_strdup(word));
}

void	command_expansions(t_env *env, t_token *content)
{
	char	*str;

	if (!env || !content)
		return ;
	str = NULL;
	if (!ft_strchr("./", *(content->literal)) && content->type & COMMAND)
		str = check_expansion(env, content->literal);
	if (str)
	{
		free(content->literal);
		content->literal = str;
	}
}
