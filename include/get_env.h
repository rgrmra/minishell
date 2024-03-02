/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:22:22 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/02 19:26:41 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_ENV_H
# define GET_ENV_H

# include "stdlib.h"
# include <stdlib.h>
# include "arraylist.h"
# include "ft_string.h"

typedef struct s_var	t_var;

struct s_var
{
	char	*name;
	char	**values;
};

enum e_status
{
	FAILURE,
	SUCCESS
};

void	envadd(t_arraylist **var, char *name, char *values);
void	envclear(t_arraylist **var);
void	envdel(t_arraylist **var, char *name);
t_var	**envget(t_arraylist **var, char *name);
void	envnew(char **env, t_arraylist **var);
void	envprint(t_arraylist **var);

#endif
