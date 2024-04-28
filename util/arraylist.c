/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:43:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 19:17:17 by rde-mour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"
#include "ft_stdlib.h"
#include <stdlib.h>

void	*arradd(t_arraylist **array, void *node)
{
	t_arraylist	*arr;

	if (!array || !(*array)->list || !node)
		return (NULL);
	arr = *array;
	if (arr->index == arr->size - 1)
	{
		arr->list = (void *)ft_mexpand(arr->list, sizeof(void *) * arr->size
				* 2, sizeof(void *) * arr->index);
		if (!arr->list)
			return (NULL);
		arr->size *= 2;
	}
	arr->list[arr->index] = node;
	arr->index++;
	arr->list[arr->index] = NULL;
	return (arr->list[arr->index - 1]);
}

void	arrdel(t_arraylist **array, void *node, int (*compare)(void *, void *),
		void (*delete)(void *))
{
	t_arraylist	*arr;
	size_t		i;
	size_t		j;

	if (!array || !(*array)->list || !node || !compare)
		return ;
	arr = *array;
	i = 0;
	while (arr->list[i])
	{
		if (compare(arr->list[i], node))
		{
			if (delete)
				delete (arr->list[i]);
			if (arr->index > 1)
			{
				j = --i;
				while (j++ < arr->index)
					arr->list[j] = arr->list[j + 1];
			}
			arr->index--;
		}
		i++;
	}
}

void	arrclear(t_arraylist **array, void (*delete)(void *))
{
	t_arraylist	*arr;

	if (!array || !(*array)->list)
		return ;
	arr = *array;
	while (arr->index--)
	{
		if (delete)
			delete (arr->list[arr->index]);
	}
	free(arr->list);
	free(arr);
}

void	*arrget(t_arraylist **array, void *node, int (*compare)(void *, void *))
{
	t_arraylist	*arr;
	size_t		i;

	if (!array || !(*array)->list || !node | !compare)
		return (NULL);
	arr = *array;
	i = 0;
	while (i < arr->index)
	{
		if (compare(arr->list[i], node))
			return (arr->list[i]);
		i++;
	}
	return (NULL);
}

t_arraylist	*arrnew(void)
{
	t_arraylist	*arr;

	arr = (t_arraylist *)ft_calloc(1, sizeof(t_arraylist));
	if (!arr)
		return (arr);
	arr->list = (void *)ft_calloc(ARRAY_SIZE, sizeof(void *));
	if (!arr->list)
		return (arr);
	arr->size = ARRAY_SIZE;
	arr->index = 0;
	return (arr);
}
