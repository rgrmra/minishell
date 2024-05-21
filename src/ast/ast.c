/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 08:42:24 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/21 12:23:00 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "types.h"
#include "ft_linkedlist.h"
#include "ft_string.h"
#include "prompt.h"
#include "tokenizer.h"
#include <linux/limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

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

t_ast	*ast_clear(t_ast *ast)
{
	if (!ast)
		return (NULL);
	if (ast->left)
		ast_clear(ast->left);
	if (ast->right)
		ast_clear(ast->right);
	if (ast->content->type & END)
		unlink(ast->content->literal);
	free(ast->content->literal);
	free(ast->content);
	free(ast);
	ast = NULL;
	return (NULL);
}

static t_ast	*ast_get(t_env *env, t_ast **paren)
{
	char	**splitted;
	t_list	*tokens;
	t_ast	*tmp;
	char	*literal;

	literal = ft_strdup(((*paren)->content->literal));
	literal[0] = ' ';
	literal[ft_strlen(literal) - 1] = ' ';
	splitted = format_input(&literal);
	tokens = tokenizer(splitted);
	if (splitted)
		free(splitted);
	tmp = ast_new(&tokens);
	if (!tmp)
	{
		env->execute = true;
		g_status = 2;
	}
	(*paren)->left = tmp;
	return (*paren);
}

t_ast	*ast_node(t_list **tokens)
{
	t_env	*env;
	t_list	*tmp;
	t_ast	*ast;

	if (!tokens || !(*tokens))
		return (NULL);
	env = tenv(NULL);
	ast = (t_ast *)malloc(1 * sizeof(t_ast));
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
	return (ast_get(env, &ast));
}

t_ast	*ast_new(t_list **tokens)
{
	t_ast	*ast;
	t_ast	*root;
	t_env	*env;

	if (!tokens || !(*tokens))
		return (NULL);
	root = NULL;
	env = tenv(NULL);
	while (*tokens)
	{
		ast = NULL;
		ast = ast_build(tokens, &ast);
		root = ast_build_operators(tokens, &root, &ast);
	}
	if (env->execute)
		root = ast_clear(root);
	return (root);
}
