/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:40:39 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/02 19:28:54 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_stdlib.h"
#include "ft_string.h"
#include "arraylist.h"
#include "get_env.h"

static int	compare(t_var *src, char *str)
{
	if (!src || !src->name || !str || !(*str))
		return (FAILURE);
	if (!ft_strncmp(src->name, str, ft_strlen(src->name) + 1))
		return (SUCCESS);
	return (FAILURE);
}

static int	delete(t_var **list)
{
	size_t	i;

	if (!list || !(*list))
		return (FAILURE);
	if ((*list)->name)
		free((*list)->name);
	i = 0;
	if ((*list)->values)
	{
		while ((*list)->values[i])
			free((*list)->values[i++]);
		free((*list)->values);
	}
	free(*list);
	*list = NULL;
	return (SUCCESS);
}

void	envdel(t_arraylist **var, char *name)
{
	if (!var || !(*var) || !name)
		return ;
	(*var)->del(var, name, &compare, &delete);
}

void	envclear(t_arraylist **var)
{
	if (!var || !(*var))
		return ;
	(*var)->clear(var, &delete);
}

t_var	**envget(t_arraylist **var, char *name)
{
	if (!var || !(*var) || !name)
		return (NULL);
	return ((t_var **)(*var)->get(var, name, &compare));
}