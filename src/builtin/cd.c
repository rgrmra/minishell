/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:03:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/24 00:12:05 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "execution.h"
#include "expansions.h"
#include "get_env.h"
#include "builtin.h"
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

static char	*get_newpwd(t_env *env, char **cmd)
{
	t_var	*var_pwd;

	if (!cmd[1] || ft_strncmp(cmd[1], "~", 2) == 0)
	{
		var_pwd = envget(&env->vars, "HOME");
		if (var_pwd)
			return (*var_pwd->values);
		panic(*cmd, NULL, "HOME not set", EXIT_FAILURE);
		return (NULL);
	}
	return (cmd[1]);
}

void	builtin_cd(t_env *env, char **cmd)
{
	char	*pwd;
	char	*new_pwd;

	g_status = EXIT_SUCCESS;
	if (check_flags(cmd))
		return ;
	if (cmd[1] && cmd[2])
	{
		panic(*cmd, NULL, "too many arguments", EXIT_FAILURE);
		return ;
	}
	pwd = get_pwd();
	new_pwd = get_newpwd(env, cmd);
	if (!pwd || !new_pwd || chdir(new_pwd))
	{
		panic("cd", cmd[1], "No such file or directory", EXIT_FAILURE);
		free(pwd);
		free(new_pwd);
		return ;
	}
	envaddx(&env->vars, "OLDPWD", pwd);
	free(pwd);
	pwd = get_pwd();
	envaddx(&env->vars, "PWD", pwd);
	free(pwd);
}
