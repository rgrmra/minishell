/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:09:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/02 22:13:31 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_stdio.h"
#include <stdlib.h>
#include "prompt.h"
#include "types.h"

static void	prompt(void)
{
	char	*prompt;

	while (true)
	{
		prompt = readline("minishell $> ");
		if (!prompt)
			break ;
		ft_putendl(prompt);
		add_history(prompt);
		free(prompt);
	}
}

int	main(void)
{
	prompt();
	rl_clear_history();
	return (EXIT_SUCCESS);
}
