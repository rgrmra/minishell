/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:22:22 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/09 21:18:05 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_ENV_H
# define GET_ENV_H

# include "arraylist.h"

# define STDPATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

typedef struct s_var	t_var;

struct		s_var
{
	char	*name;
	char	**values;
	char	*deflt;
};

void	envadd(t_arraylist **var, char *name, char *values);
void	envclear(t_arraylist **var);
void	envdel(t_arraylist **var, char *name);
t_var	*envget(t_arraylist **var, char *name);
void	envnew(t_arraylist **var, char **envp);
void	envprint(t_arraylist **var);
char	**envexport(t_arraylist *var);

#endif
