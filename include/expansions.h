/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 08:57:37 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 18:36:52 by rde-mour         ###   ########.fr       */
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
	char		**environ;
};

void	var_expansions(t_env *env, t_token *content);
void	command_expansions(t_env *env, char **content);
void	remove_quotes(char **word);
void	remove_quotes_aux(char *word);

#endif
