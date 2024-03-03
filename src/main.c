/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:09:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/03 19:40:34 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_stdio.h"
#include "prompt.h"
#include "types.h"

static void	prompt(void)
{
	char	*input;

	while (true)
	{
		input = readline("$> ");
		if (!input)
			break ;
		else
			add_history(input);
		ft_putendl(input);
		free(input);
	}
	rl_clear_history();
}

int	main(void)
{
	prompt();
	return (EXIT_SUCCESS);
}
