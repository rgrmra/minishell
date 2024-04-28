/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:09:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/27 09:50:13 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "prompt.h"
#include "expansions.h"
#include "get_env.h"

volatile sig_atomic_t	g_status = 0;

int	main(void)
{
	extern char	**environ;
	t_env		env;

	env.vars = arrnew();
	env.environ = environ;
	envnew(&env.vars, environ);
	envadd(&env.vars, "VAR", " -la");
	prompt(&env);
	envclear(&env.vars);
	return (EXIT_SUCCESS);
}
