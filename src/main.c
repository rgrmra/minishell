/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:09:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/22 09:30:25 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "expansions.h"
#include "get_env.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	env;

	if (argc > 1 || !argv)
		return (EXIT_FAILURE);
	env.vars = arrnew();
	envnew(&env.vars, envp);
	envadd(&env.vars, "VAR", "o oi");
	prompt(&env);
	envclear(&env.vars);
	return (EXIT_SUCCESS);
}
