/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:36:00 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 19:15:59 by rde-mour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAYLIST_H
# define ARRAYLIST_H

# include <stdlib.h>

# define ARRAY_SIZE 16

typedef struct s_arraylist	t_arraylist;

struct						s_arraylist
{
	size_t					size;
	size_t					index;
	void					**list;
};

void						*arradd(t_arraylist **array, void *node);
void						arrclear(t_arraylist **array, void (*f)());
void						*arrget(t_arraylist **array, void *node,
								int (*c)());
void						arrdel(t_arraylist **array, void *node, int (*c)(),
								void (*f)());
t_arraylist					*arrnew(void);

#endif
