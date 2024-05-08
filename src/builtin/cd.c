/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:03:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/07 17:24:51 by rde-mour         ###   ########.org.br   */
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

void	check_dir(char *pwd)
{
	struct stat	path_stat;

	ft_memset(&path_stat, '\0', sizeof(path_stat));
	stat((const char *) pwd, &path_stat);
	if (path_stat.st_mode & S_IFDIR)
	{
		panic("cd", pwd, "No such file or directory", 1);
		g_status = 1;
	}
}


void	builtin_cd(t_env *env, char **args)
{
	char	*pwd;
	t_var	*var_pwd;
	char	*new_pwd;

	g_status = 0;
	if (check_flags(args))
		return ;
	if (args[1] && args[2])
	{
		panic(*args, NULL, "too many arguments", 1);
		g_status = 1;
		return ;
	}
	if (!args[1] || ft_strncmp(args[1], "~", 2) == 0)
	{
		var_pwd = envget(&env->vars, "HOME");
		if (!var_pwd)
		{
			panic(*args, NULL, "HOME not set", 1);
			return ;
		}
		new_pwd = *var_pwd->values;
	}
	else
		new_pwd = args[1];
	check_dir(new_pwd);
	pwd = get_pwd();
	chdir(new_pwd);
	envadd(&env->vars, "OLD_PWD", pwd);
	envadd(&env->vars, "PWD", new_pwd);
	free(pwd);
}
