/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:09:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/06 20:56:32 by rde-mour         ###   ########.org.br   */
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
	ft_hshset(env.builtins, "cd", builtin_cd);
	ft_hshset(env.builtins, "pwd", builtin_pwd);
	ft_hshset(env.builtins, "export", builtin_export);
	ft_hshset(env.builtins, "unset", builtin_unset);
	ft_hshset(env.builtins, "env", builtin_env);
	ft_hshset(env.builtins, "exit", builtin_exit);
	env.vars = arrnew();
	env.environ = environ;
	envnew(&env.vars, environ);
	prompt(&env);
	envclear(&env.vars);
	ft_hshfree(env.builtins);
	return (EXIT_SUCCESS);
}
