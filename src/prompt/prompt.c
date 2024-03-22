/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:00:16 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/21 20:06:42 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "ft_linkedlist.h"
#include "tokens.h"
#include "types.h"
#include "ast.h"
#include "parser.h"
#include "expansions.h"
#include "prompt.h"

static void	tokens(t_env *env, char **splitted)
{
	t_list	*tokens;
	t_ast	*ast;

	tokens = tokenizer(splitted);
	parser(&tokens);
	var_expansions(env, &tokens);
	command_expansions(env, &tokens);
	ast = ast_new(&tokens);
	ast_print(&ast);
}

void	prompt(t_env *env)
{
	char	*input;
	char	**splitted;

	while (true)
	{
		input = readline("$ ");
		if (!input)
			break ;
		else if (*input)
			add_history(input);
		splitted = format_input(input);
		tokens(env, splitted);
		if (splitted)
			free(splitted);
		free(input);
	}
	rl_clear_history();
}
