/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:09:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/09 17:58:08 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_stdio.h"
#include "ft_string.h"
#include "prompt.h"
#include "types.h"
#include "tokens.h"
#include "ft_linkedlist.h"

static void	prompt(void)
{
	t_list	*tokens;
	t_list	*tmp;
	char	*input;
	char	**splitted;
	//int		i;

	while (true)
	{
		input = readline("$> ");
		if (!input)
			break ;
		else if (*input)
			add_history(input);
		splitted = format_input(input);
		//i = 0;
		//while (splitted && *(splitted + i))
		//	ft_putendl_fd(*(splitted + i++), 1);
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
