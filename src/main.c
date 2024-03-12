/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:09:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/12 14:20:36 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "prompt.h"
#include "types.h"
#include "tokens.h"
#include "ft_linkedlist.h"
#include "expansions.h"
#include "get_env.h"

static void	tokens(t_env *env, char **splitted)
{
	t_list	*tokens;
	t_list	*tmp;

	tokens = tokenizer(splitted);
	expansions(env, &tokens);
	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		printf("%d %s\n", ((t_content *) tmp->content)->token,
			((t_content *) tmp->content)->string);
		free(((t_content *) tmp->content)->string);
		free(tmp->content);
		free(tmp);
	}
}

static void	prompt(t_env *env)
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
		tokens(env, splitted);
		if (splitted)
			free(splitted);
		free(input);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_env	env;

	if (argc > 1 || !argv)
		return (EXIT_FAILURE);
	env.envp = arrnew();
	env.exports = arrnew();
	envadd(&env.envp, "VAR", "Roger de Moura");
	envnew(&env.envp, envp);
	prompt(&env);
	envclear(&env.envp);
	envclear(&env.exports);
	return (EXIT_SUCCESS);
}
