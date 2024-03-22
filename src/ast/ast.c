/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 08:42:24 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/22 10:27:14 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "tokenizer.h"
#include "ast.h"

static t_ast	*ast_node(t_list *tokens)
{
	t_ast	*ast;

	if (!tokens)
		return (NULL);
	ast = (t_ast *) malloc(1 * sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->left = NULL;
	ast->right = NULL;
	ast->content = tokens->content;
	return (ast);
}

static t_ast	*ast_build_command(t_list **tokens, t_ast *prev)
{
	t_list	*tmp;
	t_ast	*ast;

	if (!tokens || !(*tokens))
		return (prev);
	if (prev && prev->content && prev->content->token & (AND_IF | OR_IF))
		return (prev);
	tmp = *tokens;
	ast = ast_node(*tokens);
	*tokens = (*tokens)->next;
	free(tmp);
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
	if (*ast && (*ast)->content && (*ast)->content->token & (AND_IF | OR_IF)
		&& tmp->content->token & (AND_IF | OR_IF))
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
	printf("%d %s\n", tmp->content->token, tmp->content->string);
	free(tmp->content->string);
	free(tmp->content);
	free(tmp);
}

t_ast	*ast_new(t_list	**tokens)
{
	t_list	*tmp;
	t_ast	*ast;

	if (!tokens)
		return (NULL);
	tmp = *tokens;
	while (tmp)
	{
		if (!((t_content *) tmp->content)->token)
		{
			printf("syntax error near unexpected token %s\n",
				((t_content *) tmp->content)->string);
			ft_lstclear(tokens, &token_clear);
			return (NULL);
		}
		tmp = tmp->next;
	}
	ast = NULL;
	ast_build(tokens, &ast);
	return (ast);
}