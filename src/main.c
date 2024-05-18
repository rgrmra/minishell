/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:09:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/14 20:16:26 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "ft_stdio.h"
#include "get_env.h"
#include "prompt.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_hashmap.h"
#include <sys/wait.h>
#include "builtin.h"

volatile sig_atomic_t	g_status = 0;

void	sigint_handler(int sig)
{
	g_status = 128 + sig;
	ft_putendl("");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(void)
{
	struct sigaction	sa;
	extern char			**environ;
	t_env				env;

	sa = (struct sigaction){0};
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, 0);
	signal(SIGQUIT, SIG_IGN);
	env.builtins = ft_hshnew(NULL);
	env.stdss = ft_hshnew(NULL);
	ft_hshset(env.builtins, "echo", builtin_echo);
	ft_hshset(env.builtins, "cd", builtin_cd);
	ft_hshset(env.builtins, "pwd", builtin_pwd);
	ft_hshset(env.builtins, "export", builtin_export);
	ft_hshset(env.builtins, "unset", builtin_unset);
	ft_hshset(env.builtins, "env", builtin_env);
	ft_hshset(env.builtins, "exit", builtin_exit);
	env.vars = arrnew();
	envnew(&env.vars, environ);
	env.environ = envexport(env.vars);
	if (!envget(&env.vars, "PATH"))
		envadd(&env.vars, "PATH", STDPATH);
	prompt(&env);
}
