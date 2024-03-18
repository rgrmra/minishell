/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 08:42:24 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/18 11:51:36 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "tokens.h"
#include "ast.h"

static t_ast	*ast_node(t_list *tokens)
{
	t_ast	*ast;

	if (!tokens)
		return (NULL);
	ast	= (t_ast *) malloc(1 * sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->left = NULL;
	ast->right = NULL;
	ast->content = tokens->content;
	return (ast);
}

static t_ast	*ast_build(t_list **tokens)
{
	t_list	*tmp;
	t_ast	*ast;

	if (!tokens)
		return (NULL);
	if (!(*tokens))
		return (NULL);
	tmp = *tokens;
	ast = ast_node(*tokens);
	*tokens = (*tokens)->next;
	free(tmp);
	if (!ast)
		return (NULL);
	if (ast->content->token  & (SUB_IN | AND_IF | OR_IF))
		ast->right = ast_build(tokens);
	ast->left = ast_build(tokens);
	return (ast);
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
	if (!tokens)
		return (NULL);
	ast = ast_build(tokens);
	return (ast);
}
