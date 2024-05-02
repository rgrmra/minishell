/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:09:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/01 16:21:57 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "get_env.h"
#include "prompt.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_hashmap.h"
#include "builtin.h"

volatile sig_atomic_t	g_status = 0;

int	main(void)
{
	extern char	**environ;
	t_env		env;

	env.builtins = ft_hshnew(NULL);
	ft_hshset(env.builtins, "echo", builtin_echo);
	env.vars = arrnew();
	env.environ = environ;
	envnew(&env.vars, environ);
	envadd(&env.vars, "VAR", " -la");
	prompt(&env);
	envclear(&env.vars);
	ft_hshfree(env.builtins);
	return (EXIT_SUCCESS);
}
