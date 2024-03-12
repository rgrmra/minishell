/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:22:22 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/12 02:28:54 by rde-mour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_ENV_H
# define GET_ENV_H

# include "arraylist.h"
# include "ft_string.h"
# include "stdlib.h"
# include <stdlib.h>

typedef struct s_var	t_var;

struct					s_var
{
	char				*name;
	char				**values;
};

void					envadd(t_arraylist **var, char *name, char *values);
void					envclear(t_arraylist **var);
void					envdel(t_arraylist **var, char *name);
t_var					*envget(t_arraylist **var, char *name);
void					envnew(t_arraylist **var, char **envp);
void					envprint(t_arraylist **var);

#endif
