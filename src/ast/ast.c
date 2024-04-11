/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 08:42:24 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/11 20:08:28 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"
#include "ast.h"
#include "prompt.h"
#include "parser.h"
#include "ft_string.h"

//static t_ast	*ast_clear(t_ast	**ast)
//{
//	t_ast	*tmp;
//
//	if (!ast || !(*ast))
//		return (NULL);
//	tmp = *ast;
//	if ((*ast)->left)
//		ast_clear(&(*ast)->left);
//	if ((*ast)->right)
//		ast_clear(&(*ast)->right);
//	free(tmp->content->literal);
//	free(tmp->content);
//	free(tmp);
//	return (NULL);
//}

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

static t_ast	*ast_get(t_ast **paren)
{
	char	**splitted;
	t_list	*tokens;
	t_ast	*tmp;
	char	*literal;

	literal = ft_substr((*paren)->content->literal, 1,
		ft_strlen((*paren)->content->literal) - 2);
	splitted = format_input(literal);
	tokens = tokenizer(splitted);
	if (splitted)
		free(splitted);
	parser(&tokens);
	tmp = ast_new(&tokens);
	free((*paren)->content->literal);
	free((*paren)->content);
	free(literal);
	free(*paren);
	return (tmp);
}

static t_ast	*ast_node(t_list **tokens)
{
	t_list	*tmp;
	t_ast	*ast;

	if (!tokens || !(*tokens))
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
	if (ast->content->type & ~PAREN)
		return (ast);
	return (ast_get(&ast));
}

static t_ast	*ast_build_command(t_list **tokens)
{
	t_ast	*ast;
	t_ast	*tmp;

	if (!tokens || !(*tokens))
		return (NULL);
	ast = ast_node(tokens);
	if (ast && ast->content->type & (LESS | DLESS | GREATER | DGREATER))
	{
		if ((*tokens) && (*tokens)->content
				&& ((t_token *)(*tokens)->content)->type & (FILENAME | END))
			ast->left = ast_node(tokens);
		if ((*tokens) && (*tokens)->content
				&& ((t_token *)(*tokens)->content)->type & (COMMAND | PAREN))
			ast->right = ast_node(tokens);
	}
	if (ast->content->type & (COMMAND) && *tokens && (*tokens)->content
		&& ((t_token *)(*tokens)->content)->type & (VBAR))
	{
		tmp = ast_node(tokens);
		tmp->left = ast;
		if (*tokens && (*tokens)->content && ((t_token *)(*tokens)->content)->type & VBAR)
			tmp->right =
		tmp->right = ast_node(tokens);
		ast = tmp;
	}
	return (ast);
}

static t_ast	*ast_build(t_list **tokens, t_ast **prev)
{
	t_ast	*ast;
	t_ast	*tmp;

	if (!tokens || !(*tokens))
		return (*prev);
	ast = ast_build_command(tokens);
	if (!ast)
		return (*prev);
	if (!(*prev))
		*prev = ast;
	else if (!(*prev)->left && (ast->content->type & ~(AND | OR)
		|| (ast->content->type & (AND | OR | VBAR) && ast->left && ast->right)))
		(*prev)->left = ast;
	else if (!(*prev)->right && (ast->content->type & ~(AND | OR)
		|| (ast->content->type & (AND | OR | VBAR) && ast->left && ast->right)))
		(*prev)->right = ast;
	else
	{
		if ((*prev)->content->type & (LESS | DLESS | GREATER | DGREATER))
			ast->right = ast->left;
		ast->left = *prev;
		*prev = ast;
	}
	if (*tokens && (*tokens)->content && ((t_token *)(*tokens)->content)->type
			& (AND | OR))
	{
		tmp = ast_node(tokens);
		tmp->left = *prev;
		tmp->right = ast_new(tokens);
		return (tmp);

	}
	return (ast_build(tokens, prev));
}

t_ast	*ast_new(t_list	**tokens)
{
	t_ast	*ast;
	t_ast	*node;

	if (!tokens || !(*tokens))
		return (NULL);
	node = NULL;
	while (*tokens)
	{
		ast = NULL;
		ast = ast_build(tokens, &ast);
		if (!node)
			node = ast;
		else if (!node->left)
			node->left = ast;
		else if (!node->right)
			node->right = ast;
		else
		{
			ast->right = ast->left;
			ast->left = node;
			node =	ast;
		}
		ast = node;
	}
	return (ast);
}
