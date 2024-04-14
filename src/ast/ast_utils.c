/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:30:01 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/14 16:07:05 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast.h"

static t_ast	*ast_build_pipeline(t_list **tokens, t_ast **root, t_ast **prev)
{
	t_ast	*ast;

	ast = NULL;
	(*prev)->left = *root;
	if (*tokens && ((t_token *)(*tokens)->content)->type & (COMMAND | PAREN))
		(*prev)->right = ast_node(tokens);
	else if (*tokens && ((t_token *)(*tokens)->content)->type
			& (LESS | DLESS | GREATER | DGREATER))
		(*prev)->right = ast_build(tokens, &ast);
	return (*prev);
}

t_ast	*ast_build_command(t_list **tokens, t_ast **prev)
{
	t_ast	*ast;
	t_ast	*tmp;

	if (!tokens || !(*tokens)
		|| (*tokens && ((t_token *)(*tokens)->content)->type & (AND | OR)))
		return (*prev);
	tmp = NULL;
	ast = ast_node(tokens);
	if (ast && ast->content->type & VBAR)
		ast_build_pipeline(tokens, prev, &ast);
	return (ast);
}

static t_ast	*ast_build_redirect(t_list **tokens, t_ast **root, t_ast **prev)
{
	if (!tokens || !(*tokens))
		return (*prev);
	if (*root && (*root)->content->type & (LESS | DLESS | GREATER | DGREATER))
	{
		(*prev)->left = *root;
		(*prev)->right = ast_node(tokens);
		return (*prev);
	}
	if (*tokens && ((t_token *)(*tokens)->content)->type & (FILENAME | END))
		(*prev)->left = ast_node(tokens);
	if (*tokens && ((t_token *)(*tokens)->content)->type & (COMMAND | PAREN))
		(*prev)->right = ast_node(tokens);
	if (*root)
	{
		(*root)->right = *prev;
		return (*root);
	}
	return (*prev);
}

t_ast	*ast_build_operators(t_list	**tokens, t_ast **root, t_ast **prev)
{
	t_ast	*tmp;

	if (*tokens && !(*root))
		*root = ast_node(tokens);
	if (*root && !(*root)->left)
		(*root)->left = *prev;
	else if (*root && !(*root)->right)
		(*root)->right = *prev;
	else if (*tokens && *root)
	{
		tmp = ast_node(tokens);
		tmp->left = *root;
		tmp->right = *prev;
		*root = tmp;
	}
	else
		return (*prev);
	return (*root);
}

t_ast	*ast_build(t_list **tokens, t_ast **prev)
{
	t_ast	*ast;

	if (!tokens || !(*tokens)
		|| (*tokens && ((t_token *)(*tokens)->content)->type & (AND | OR)))
		return (*prev);
	if (*tokens && ((t_token *)(*tokens)->content)->type & PAREN)
		return (ast_node(tokens));
	ast = ast_node(tokens);
	if (!ast)
		return (*prev);
	if (ast->content->type & COMMAND)
		ast = ast_build_command(tokens, &ast);
	else if (ast->content->type & (LESS | DLESS | GREATER | DGREATER))
		ast = ast_build_redirect(tokens, prev, &ast);
	else if (ast->content->type & VBAR)
		ast = ast_build_pipeline(tokens, prev, &ast);
	return (ast_build(tokens, &ast));
}
