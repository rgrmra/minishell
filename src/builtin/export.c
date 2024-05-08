/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:08:45 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/07 21:28:16 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "builtin.h"
#include "ft_string.h"
#include "execution.h"
#include "expansions.h"
#include "get_env.h"
#include <signal.h>

extern volatile sig_atomic_t	g_status;

static void	export_arg(t_env *env, char *arg)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = ft_substr(arg, 0, i + 1);
	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		panic("export", key, "not a valid identifier", 1);
		free(key);
		g_status = 1;
		return ;
	}
	key[i] = '\0';
	if (!arg[i++])
	{
		free(key);
		return ;
	}
	value = ft_substr(arg, i, ft_strlen(arg));
	envadd(&env->vars, key, value);
	free(key);
	free(value);
}

void	builtin_export(t_env *env, char **args)
{
	int i;

	g_status = 0;
	if (check_flags(args))
		return ;
	i = 0;
	while (args[++i])
		export_arg(env, args[i]);
	if (i == 1)
		envprint(&env->vars);
}
