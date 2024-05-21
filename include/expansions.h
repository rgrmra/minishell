/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 08:57:37 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/20 20:13:47 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "ast.h"
# include "arraylist.h"
# include "ft_hashmap.h"
# include "termio.h"

typedef struct s_env	t_env;

struct					s_env
{
	t_arraylist			*vars;
	t_hashmap			*builtins;
	t_ast				*ast;
	int					redisplay;
	int					execute;
	struct termios		fd;
};

void	hshfdsclear(t_env *env);
void	var_expansions(t_env *env, char	**content);
char	*check_expansion(t_env *env, char *word);
void	command_expansions(t_env *env, char **content);
void	remove_quotes(char **word);
void	remove_quotes_aux(char *word);

#endif
