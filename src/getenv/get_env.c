/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:36:57 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/22 22:31:36 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"
#include "ft_stdio.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "utils.h"
#include "get_env.h"
#include <stdlib.h>
#include <unistd.h>

void	envnew(t_arraylist **var, char **env)
{
	size_t	size;
	char	*tmp;
	t_var	*content;

	if (!env || !var)
		return ;
	while (*env)
	{
		tmp = ft_strchr(*env, '=');
		size = ++tmp - (*env) - 1;
		content = (t_var *)ft_calloc(1, sizeof(t_var));
		if (!content)
			return ;
		content->name = ft_substr(*env, 0, size);
		content->values = ft_split(tmp, ':');
		content->deflt = ft_strdup(*env);
		arradd(var, content);
		env++;
	}
}

void	envadd(t_arraylist **var, char *name, char *values)
{
	t_var	*content;

	content = (t_var *)ft_calloc(1, sizeof(t_var));
	if (!content)
		return ;
	content->name = ft_strdup(name);
	content->values = ft_split(values, ':');
	content->deflt = ft_strdup(values);
	envdel(var, name);
	arradd(var, content);
}

void	envaddx(t_arraylist **var, char *name, char *values)
{
	t_var	*content;

	content = (t_var *)ft_calloc(1, sizeof(t_var));
	if (!content)
		return ;
	content->name = ft_strdup(name);
	content->values = ft_split(values, ':');
	content->deflt = strjoinsep(name, values, '=');
	envdel(var, name);
	arradd(var, content);
}

void	envprint(t_arraylist **var)
{
	t_var	*content;
	size_t	i;

	i = 0;
	while (i < (*var)->size)
	{
		content = (*var)->list[i++];
		if (!content)
			break ;
		ft_putendl(content->deflt);
	}
}

char	**envexport(t_arraylist *var)
{
	t_var	*content;
	char	**env;
	size_t	i;

	i = 0;
	env = (char **) malloc(sizeof(char *) * var->size);
	if (!env)
		return (NULL);
	while (var->list[i])
	{
		content = var->list[i];
		env[i] = ft_strdup(content->deflt);
		i++;
	}
	env[i] = NULL;
	return (env);
}
