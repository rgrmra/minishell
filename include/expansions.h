/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 08:57:37 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/13 09:56:19 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "arraylist.h"
# include "ft_linkedlist.h"

typedef struct s_env	t_env;

struct s_env
{
	t_arraylist	*envp;
	t_arraylist	*exports;
};

void	command_expansions(t_env *env, t_list **tokens);
void	var_expansions(t_env *env, t_list **tokens);

#endif
