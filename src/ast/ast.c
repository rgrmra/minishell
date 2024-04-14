/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 08:42:24 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/14 15:43:15 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "ft_linkedlist.h"
#include "tokenizer.h"
#include "ast.h"
#include "prompt.h"
#include "parser.h"
#include "ft_string.h"

t_ast	*ast_clear(t_ast **ast)
{
	t_ast	*tmp;

	if (!ast || !(*ast))
		return (NULL);
	tmp = *ast;
	if ((*ast)->left)
		ast_clear(&(*ast)->left);
	if ((*ast)->right)
		ast_clear(&(*ast)->right);
	free(tmp->content->literal);
	free(tmp->content);
	free(tmp);
	return (NULL);
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
	free(literal);
	(*paren)->content->literal = ft_strdup("SUBSHELL");
	(*paren)->left = tmp;
	return (*paren);
}

t_ast	*ast_node(t_list **tokens)
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

t_ast	*ast_new(t_list	**tokens)
{
	t_ast	*ast;
	t_ast	*root;

	if (!tokens || !(*tokens))
		return (NULL);
	root = NULL;
	while (*tokens)
	{
		ast = NULL;
		ast = ast_build(tokens, &ast);
		root = ast_build_operators(tokens, &root, &ast);
	}
	return (root);
}
