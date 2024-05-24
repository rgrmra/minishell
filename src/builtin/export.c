/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:08:45 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/22 22:26:07 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_ctype.h"
#include "ft_string.h"
#include "builtin.h"
#include "ft_string.h"
#include "execution.h"
#include "expansions.h"
#include "get_env.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

extern volatile sig_atomic_t	g_status;

void	sort_vars(char **argv, int minor)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		minor = i;
		j = i;
		while (argv[j])
		{
			if (ft_strncmp(argv[j], argv[minor], ft_strlen(argv[j] + 1)) < 0)
				minor = j;
			j++;
		}
		if (i != minor)
		{
			tmp = argv[i];
			argv[i] = argv[minor];
			argv[minor] = tmp;
		}
		i++;
	}
}

static void	export_arg(t_env *env, char *arg)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (i > 0 && !ft_isalnum(arg[i]))
			g_status = 1;
		i++;
	}
	key = ft_substr(arg, 0, i + 1);
	if (g_status == 1 || (!ft_isalpha(key[0]) && key[0] != '_'))
	{
		panic("export", key, "not a valid identifier", EXIT_FAILURE);
		g_status = EXIT_FAILURE;
		return (free(key));
	}
	key[i] = '\0';
	if (!arg[i++])
		return (free(key));
	value = ft_substr(arg, i, ft_strlen(arg));
	envaddx(&env->vars, key, value);
	free(key);
	free(value);
}

void	builtin_export(t_env *env, char **cmd)
{
	char	**vars;
	int		i;

	g_status = EXIT_SUCCESS;
	if (check_flags(cmd))
		return ;
	i = 0;
	while (cmd[++i])
		export_arg(env, cmd[i]);
	if (i == 1)
	{
		vars = envexport(env->vars);
		sort_vars(vars, 0);
		i = 0;
		while (vars[i])
			ft_putendl_fd(vars[i++], STDOUT_FILENO);
		ft_freesplit(vars);
	}
}
