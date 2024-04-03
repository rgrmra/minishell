/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:09:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/02 22:51:09 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "prompt.h"
#include "expansions.h"
#include "get_env.h"

int	main(void)
{
	extern char	**environ;
	t_env		env;

	env.vars = arrnew();
	envnew(&env.vars, environ);
	envadd(&env.vars, "VAR", "o oi");
	prompt(&env);
	envclear(&env.vars);
	return (EXIT_SUCCESS);
}
