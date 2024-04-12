/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 08:42:24 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/11 22:02:10 by rde-mour         ###   ########.org.br   */
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
t_ast	*ast_build(t_list **tokens, t_ast **prev);

t_ast	*ast_build_command(t_list **tokens, t_ast **prev)
{
	t_ast	*ast;

	ast = ast_node(tokens);
	if (ast->content->type & VBAR)
	{
		ast->left = *prev;
		ast->right = ast_node(tokens);
	}
	return (ast_build(tokens, &ast));
}

t_ast	*ast_build_redirect(t_list **tokens, t_ast **prev)
{
	if (*tokens && ((t_token *)(*tokens)->content)->type & (FILENAME | END))
		(*prev)->left = ast_node(tokens);
	if (*tokens && ((t_token *)(*tokens)->content)->type & (COMMAND | PAREN))
		(*prev)->right = ast_node(tokens);
	return (*prev);
}

t_ast	*ast_build_pipeline(t_list **tokens, t_ast **root, t_ast **prev)
{
	//t_ast	*ast;

	(*prev)->left = *root;
	if (*tokens && ((t_token *)(*tokens)->content)->type & (COMMAND | PAREN))
		(*prev)->right = ast_node(tokens);

	return (*prev);
}

t_ast	*ast_build(t_list **tokens, t_ast **prev)
{
	t_ast	*ast;

	if (!tokens || !(*tokens))
		return (*prev);
	ast = ast_node(tokens);
	if (!ast)
		return (*prev);
	if (ast->content->type & COMMAND)
		ast = ast_build_command(tokens, &ast);
	else if (ast->content->type & (LESS | DLESS | GREATER | DGREATER))
		ast = ast_build_redirect(tokens, &ast);
	else if (ast->content->type & VBAR)
		ast = ast_build_pipeline(tokens, prev, &ast);
	return (ast_build(tokens, &ast));
}

t_ast	*ast_new(t_list	**tokens)
{
	t_ast	*ast;

	if (!tokens || !(*tokens))
		return (NULL);
	ast = NULL;
	ast = ast_build(tokens, &ast);
	return (ast);
}
