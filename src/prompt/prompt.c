/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:00:16 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/08 21:40:53 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "ft_linkedlist.h"
#include "tokenizer.h"
#include "types.h"
#include "ast.h"
#include "parser.h"
#include "expansions.h"
#include "prompt.h"

static void	tokens(t_env *env, char **splitted)
{
	t_list	*tokens;
	t_ast	*ast;
	//t_list	*clear;
	//t_list	*tmp;

	tokens = tokenizer(splitted);
	if (splitted)
		free(splitted);
	parser(&tokens);
	(void)env;
	//tmp = tokens;
	//while (tmp)
	//{
	//	//clear = tmp;
	//	var_expansions(env, (t_token *) tmp->content);
	//	command_expansions(env, (t_token *) tmp->content);
	//	remove_quotes(((t_token *) tmp->content)->literal);
	//	//printf("%s ", ((t_token *) tmp->content)->literal);
	//	tmp = tmp->next;
	//	//free(((t_token *) clear->content)->literal);
	//	//free(clear->content);
	//	//free(clear);
	//}
	//printf("\n");
	ast = ast_new(&tokens);
	ast_print(&ast);
}

void	prompt(t_env *env)
{
	char	*input;

	while (true)
	{
		input = readline("$ ");
		if (!input)
			break ;
		else if (*input != '\0')
			add_history(input);
		tokens(env, format_input(input));
		free(input);
	}
	rl_clear_history();
}
