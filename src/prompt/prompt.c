/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:00:16 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/31 19:32:50 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "expansions.h"
#include "ft_linkedlist.h"
#include "ft_string.h"
#include "prompt.h"
#include "tokenizer.h"
#include "types.h"
#include "errors.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <termio.h>

extern volatile sig_atomic_t	g_status;

static void	run(t_env *env, char **splitted)
{
	t_list	*run;
	t_ast	*ast;

	env->execute = false;
	run = tokenizer(splitted);
	if (splitted)
		free(splitted);
	ast = ast_new(&run);
	env->ast = ast;
	execute(env, ast);
	ast_clear(ast);
}

void	prompt(t_env *env)
{
	struct termios	fd;
	char			*input;

	fd = (struct termios){0};
	tcgetattr(STDIN_FILENO, &fd);
	while (true)
	{
		env->redisplay = false;
		input = readline("$ ");
		env->redisplay = true;
		if (!input)
			input = ft_strdup("exit");
		else if (*input != '\0')
			add_history(input);
		run(env, format_input(&input));
		tcsetattr(STDIN_FILENO, TCSANOW, &fd);
	}
}
