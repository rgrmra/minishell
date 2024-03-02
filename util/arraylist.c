/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:43:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/02 19:13:18 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"
#include "ft_stdlib.h"
#include <stdlib.h>

void	**arradd(t_arraylist **array, void **node)
{
	t_arraylist	*arr;

	if (!array || !(*array)->list || !node || !(*node))
		return (NULL);
	arr = *array;
	if (arr->index >= arr->size)
	{
		arr->list = (void *) ft_mexpand(arr->list,
				sizeof(void *) * arr->size * 2,
				sizeof(void *) * arr->index);
		if (!arr->list)
			return (NULL);
		arr->size *= 2;
	}
	arr->list[arr->index] = *node;
	arr->index++;
	return (node);
}

void	arrdel(t_arraylist **array, void *node, int (*c)(), void (*f)())
{
	t_arraylist	*arr;
	size_t		i;

	if (!array || !(*array)->list || !node || !c)
		return ;
	arr = *array;
	i = 0;
	while (i < arr->index)
	{
		if (c(arr->list[i], node))
		{
			if (f)
				f(&arr->list[i]);
			if (arr->index > 1)
			{
				arr->list[i] = arr->list[arr->index - 1];
				arr->index--;
				i--;
			}
		}
		i++;
	}
}

void	arrclear(t_arraylist **array, void (*f)())
{
	t_arraylist	*arr;

	if (!array || !(*array)->list)
		return ;
	arr = *array;
	while (arr->index--)
	{
		if (f)
			f(&arr->list[arr->index]);
	}
	free(arr->list);
	free(arr);
}

void	**arrget(t_arraylist **array, void *node, int (*c)())
{
	t_arraylist	*arr;
	size_t		i;

	if (!array || !(*array)->list || !node | !c)
		return (NULL);
	arr = *array;
	i = 0;
	while (i < arr->index)
	{
		if (c(arr->list[i], node))
			return (&arr->list[i]);
		i++;
	}
	return (NULL);
}

t_arraylist	*arrnew(void)
{
	t_arraylist	*arr;

	arr = (t_arraylist *) ft_calloc(1, sizeof(t_arraylist));
	if (!arr)
		return (arr);
	arr->list = (void *) ft_calloc(ARRAY_SIZE, sizeof(void *));
	if (!arr->list)
		return (arr);
	arr->size = ARRAY_SIZE;
	arr->index = 0;
	arr->add = &arradd;
	arr->clear = &arrclear;
	arr->get = &arrget;
	arr->del = &arrdel;
	return (arr);
}
