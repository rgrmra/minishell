/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 08:43:01 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/18 10:12:05 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "tokens.h"

typedef struct s_ast	t_ast;
struct s_ast
{
	t_ast		*left;
	t_ast		*right;
	t_content	*content;
};

void	ast_print(t_ast **ast);
t_ast	*ast_new(t_list	**tokens);

#endif