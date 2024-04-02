/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:36:57 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/02 19:43:22 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_stdlib.h"
#include "ft_string.h"
#include "arraylist.h"
#include "get_env.h"
#include "ft_stdio.h"

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
		content = (t_var *) ft_calloc(1, sizeof(t_var));
		if (!content)
			return ;
		content->name = ft_substr(*env, 0, size);
		content->values = ft_split(tmp, ':');
		arradd(var, content);
		env++;
	}
}

void	envadd(t_arraylist **var, char *name, char *values)
{
	t_var	*content;

	content = (t_var *) ft_calloc(1, sizeof(t_var));
	if (!content)
		return ;
	content->name = ft_strdup(name);
	content->values = ft_split(values, ':');
	envdel(var, name);
	arradd(var, content);
}

void	envprint(t_arraylist **var)
{
	t_var	*content;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < (*var)->size)
	{
		content = (*var)->list[i++];
		if (!content)
			break ;
		if (content->name)
		{
			ft_putstr_fd(content->name, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
		}
		j = 0;
		while (content->values[j])
		{
			ft_putstr_fd(content->values[j++], STDOUT_FILENO);
			if (content->values[j])
				ft_putstr_fd(":", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}
