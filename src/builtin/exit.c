/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:49:21 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/04 12:12:57 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "builtin.h"
#include "ft_string.h"
#include "expansions.h"
#include "execution.h"
#include <signal.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

void	builtin_exit(t_env *env, char **args)
{
	if (args)
		ft_freesplit(args);
	rl_clear_history();
	clearall(env);
}
