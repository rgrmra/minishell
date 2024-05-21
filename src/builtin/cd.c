/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:03:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/21 13:37:07 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "execution.h"
#include "expansions.h"
#include "get_env.h"
#include "builtin.h"
#include <signal.h>
#include <sys/stat.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

static char	*get_newpwd(t_env *env, char **args)
{
	t_var	*var_pwd;

	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
	{
		var_pwd = envget(&env->vars, "HOME");
		if (var_pwd)
			return (*var_pwd->values);
		panic(*args, NULL, "HOME not set", 1);
		return (NULL);
	}
	return (args[1]);
}

void	builtin_cd(t_env *env, char **args)
{
	char	*pwd;
	char	*new_pwd;

	g_status = 0;
	if (check_flags(args))
		return ;
	if (args[1] && args[2])
	{
		panic(*args, NULL, "too many arguments", 1);
		return ;
	}
	pwd = get_pwd();
	new_pwd = get_newpwd(env, args);
	if (!new_pwd)
		return ;
	if (chdir(new_pwd))
	{
		panic("cd", args[1], "No such file or directory", 1);
		return ;
	}
	envadd(&env->vars, "OLDPWD", pwd);
	free(pwd);
	pwd = get_pwd();
	envadd(&env->vars, "PWD", pwd);
	free(pwd);
}
