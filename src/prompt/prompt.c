/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:00:16 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/27 20:47:09 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "ft_linkedlist.h"
#include "tokenizer.h"
#include "types.h"
#include "ast.h"
#include "parser.h"
#include "expansions.h"
#include "prompt.h"
#include <fcntl.h>

#include "execution.h"

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
	//ast_print(&ast);
	//ast_clear(&ast);
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
