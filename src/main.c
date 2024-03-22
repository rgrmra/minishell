/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:09:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/21 20:07:19 by rde-mour         ###   ########.org.br   */
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
	env.envp = arrnew();
	env.exports = arrnew();
	env.heredoc = arrnew();
	envadd(&env.envp, "VAR", "o oi");
	envnew(&env.envp, envp);
	prompt(&env);
	envclear(&env.envp);
	envclear(&env.exports);
	envclear(&env.heredoc);
	return (EXIT_SUCCESS);
}
