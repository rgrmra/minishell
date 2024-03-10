/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:09:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/10 15:26:00 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_string.h"
#include "prompt.h"
#include "types.h"
#include "tokens.h"
#include "ft_linkedlist.h"

static void	tokens(char **splitted)
{
	t_list	*tokens;
	t_list	*tmp;

	tokens = tokenizer(splitted);
	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		printf("%d %s\n", ((t_content *) tmp->content)->token,
			((t_content *) tmp->content)->string);
		free(tmp->content);
		free(tmp);
	}
}

static void	prompt(void)
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
			ft_memclear((void **) splitted, free);
		free(input);
	}
	rl_clear_history();
}

int	main(void)
{
	prompt();
	return (EXIT_SUCCESS);
}
