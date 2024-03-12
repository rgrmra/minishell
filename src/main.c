/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:09:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/12 01:23:03 by rde-mour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linkedlist.h"
#include "ft_string.h"
#include "prompt.h"
#include "tokens.h"
#include "types.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

static void	loop_prompt(void);
static void	tokens(char **splitted);

int	main(void)
{
	loop_prompt();
	return (EXIT_SUCCESS);
}

static void	loop_prompt(void)
{
	char	*input;
	char	**splitted;

	while (true)
	{
		input = readline("$> ");
		if (!input)
			break ;
		else if (*input)
			add_history(input);
		splitted = format_input(input);
		tokens(splitted);
		if (splitted)
			ft_memclear((void **)splitted, free);
		free(input);
	}
	rl_clear_history();
}

static void	tokens(char **splitted)
{
	t_list	*tokens;
	t_list	*tmp;

	tokens = tokenizer(splitted);
	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		printf("%d %s\n", ((t_content *)tmp->content)->token,
			((t_content *)tmp->content)->literal);
		free(tmp->content);
		free(tmp);
	}
}
