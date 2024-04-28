/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 08:43:01 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 18:36:47 by rde-mour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "tokenizer.h"

typedef struct s_ast	t_ast;
struct s_ast
{
	t_ast	*left;
	t_ast	*right;
	t_token	*content;
};

void	ast_print(t_ast **ast);
void	ast_remove(t_ast **ast);
t_ast	*ast_new(t_list **tokens);
t_ast	*ast_node(t_list **tokens);
t_ast	*ast_clear(t_ast **ast);
t_ast	*ast_build(t_list **tokens, t_ast **prev);
t_ast	*ast_build_operators(t_list	**tokens, t_ast **root, t_ast **prev);

#endif
