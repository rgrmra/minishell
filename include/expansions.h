/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 08:57:37 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/28 09:32:13 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "arraylist.h"
# include "tokenizer.h"

typedef struct s_env	t_env;

struct s_env
{
	t_arraylist	*vars;
};

void	var_expansions(t_env *env, t_token *content);
void	command_expansions(t_env *env, t_token *content);
void	remove_quotes(char *word);

#endif
