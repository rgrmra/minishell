/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:57:54 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/22 19:35:06 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
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

	if (!env)
		return (ft_strdup(""));
	path = check_bultins(word);
	if (path)
		return (NULL);
	paths = envget(&env->vars, "PATH")->values;
	if (!paths)
		return (ft_strdup(""));
	i = 0;
	while (paths[i])
	{
		path = strjoinsep(paths[i], word, '/');
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (ft_strdup(word));
}

void	command_expansions(t_env *env, t_content *content)
{
	char	*str;

	if (!env || !content)
		return ;
	str = NULL;
	if (!ft_strchr("./", *(content->string)) && content->token & COMMAND)
		str = check_expansion(env, content->string);
	if (str)
	{
		free(content->string);
		content->string = str;
	}
}
