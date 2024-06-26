/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:07:24 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/31 19:56:17 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "expansions.h"
#include "execution.h"
#include "ft_string.h"
#include "ft_stdio.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

char	*get_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		g_status = EXIT_FAILURE;
		return (ft_strdup(""));
	}
	return (pwd);
}

void	builtin_pwd(t_env *env, char **cmd)
{
	char	*pwd;

	(void)env;
	g_status = EXIT_SUCCESS;
	if (check_flags(cmd))
		return ;
	pwd = get_pwd();
	if (*pwd)
		ft_putendl_fd(pwd, STDOUT_FILENO);
	else
		panic(*cmd, NULL, "error retrieving current directory", EXIT_FAILURE);
	free(pwd);
}
