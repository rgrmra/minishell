/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:09:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/22 22:30:01 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "ft_stdio.h"
#include "types.h"
#include "get_env.h"
#include "prompt.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "ft_hashmap.h"
#include <sys/wait.h>
#include "builtin.h"

volatile sig_atomic_t	g_status = 0;

t_env	*tenv(t_env *env)
{
	static t_env	*envloc;

	if (env)
		envloc = env;
	return (envloc);
}

static void	sigint_handler(int sig)
{
	t_env	*env;

	env = tenv(NULL);
	env->execute = true;
	g_status = 128 + sig;
	if (env->redisplay == 2)
		close(STDIN_FILENO);
	ft_putstr("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	if (!env->redisplay)
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
	ft_hshset(env.builtins, "echo", builtin_echo);
	ft_hshset(env.builtins, "cd", builtin_cd);
	ft_hshset(env.builtins, "pwd", builtin_pwd);
	ft_hshset(env.builtins, "export", builtin_export);
	ft_hshset(env.builtins, "unset", builtin_unset);
	ft_hshset(env.builtins, "env", builtin_env);
	ft_hshset(env.builtins, "exit", builtin_exit);
	env.vars = arrnew();
	envnew(&env.vars, environ);
	if (!envget(&env.vars, "PATH"))
		envaddx(&env.vars, "PATH", STDPATH);
	tenv(&env);
	prompt(&env);
}
