/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 08:42:24 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/02 19:45:06 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"
#include "ast.h"

static void	ast_build(t_list **tokens, t_ast **ast);

static t_ast	*ast_node(t_list **tokens)
{
	t_list	*tmp;
	t_ast	*ast;

	if (!tokens)
		return (NULL);
	ast = (t_ast *) malloc(1 * sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->left = NULL;
	ast->right = NULL;
	ast->content = (*tokens)->content;
	tmp = *tokens;
	*tokens = (*tokens)->next;
	free(tmp);
	return (ast);
}

static t_ast	*ast_build_command(t_list **tokens, t_ast *prev)
{
	t_ast	*ast;

	if (!tokens || !(*tokens))
		return (prev);
	ast = NULL;
	if (prev && prev->content && prev->content->type & (AND | OR))
	{
		if (((t_token *)(*tokens)->content)->type & LPAREN
			&& prev->left->content->type & ~RPAREN)
		{
			ast_build(tokens, &ast);
			prev->right = ast;
		}
		return (prev);
	}
	ast = ast_node(tokens);
	if (!ast)
		return (prev);
	ast->left = prev;
	return (ast_build_command(tokens, ast));
}

static void	ast_build(t_list **tokens, t_ast **ast)
{
	t_ast	*tmp;

	if (!tokens || !(*tokens))
		return ;
	tmp = ast_build_command(tokens, NULL);
	if (!tmp)
		return ;
	if (*ast && (*ast)->content && (*ast)->content->type & (AND | OR)
		&& tmp->content->type & (AND | OR))
	{
		if (!(*ast)->right)
		{
			(*ast)->right = tmp->left;
			tmp->left = (*ast);
			(*ast) = tmp;
		}
	}
	else if (*ast)
		(*ast)->right = tmp;
	else if (!(*ast))
		*ast = tmp;
	ast_build(tokens, ast);
}

void	ast_print(t_ast **ast)
{
	t_ast	*tmp;

	if (!ast || !(*ast))
		return ;
	tmp = *ast;
	if ((*ast)->left)
		ast_print(&(*ast)->left);
	if ((*ast)->right)
		ast_print(&(*ast)->right);
	printf("%d %s\n", tmp->content->type, tmp->content->literal);
	free(tmp->content->literal);
	free(tmp->content);
	free(tmp);
}

t_ast	*ast_new(t_list	**tokens)
{
	t_ast	*ast;

	if (!tokens)
		return (NULL);
	ast = NULL;
	ast_build(tokens, &ast);
	return (ast);
}
