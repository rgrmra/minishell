/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 08:57:37 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/09 19:05:00 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "ast.h"
# include "arraylist.h"
# include "tokenizer.h"
# include "ft_hashmap.h"

typedef struct s_env	t_env;

struct					s_env
{
	t_arraylist			*vars;
	char				**environ;
	t_hashmap			*builtins;
	t_ast				*ast;
	int					stds[2];
};

void	var_expansions(t_env *env, t_token *content);
char	*check_expansion(t_env *env, char *word);
void	command_expansions(t_env *env, char **content);
void	remove_quotes(char **word);
void	remove_quotes_aux(char *word);

#endif
