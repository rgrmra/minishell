/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:00:16 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 18:38:13 by rde-mour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "expansions.h"
#include "ft_linkedlist.h"
#include "parser.h"
#include "prompt.h"
#include "tokenizer.h"
#include "types.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

static void	tokens(t_env *env, char **splitted)
{
	t_list	*tokens;
	t_ast	*ast;

	tokens = tokenizer(splitted);
	if (splitted)
		free(splitted);
	parser(&tokens);
	ast = ast_new(&tokens);
	execute(env, &ast, NULL);
	//(void)env;
	// ast_print(&ast);
	// ast_clear(&ast);
}

void	prompt(t_env *env)
{
	char	*input;

	while (true)
	{
		input = readline("$ ");
		if (!input)
			break ;
		tokens(env, format_input(input));
		if (*input != '\0')
			add_history(input);
		free(input);
		printf("%d\n", g_status);
	}
	rl_clear_history();
}
