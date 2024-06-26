/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:09:24 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/20 21:45:37 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "expansions.h"
# include <readline/history.h>
# include <readline/readline.h>

t_env	*tenv(t_env *env);
int		find_quote(char *tmp);
char	**format_input(char **input);
void	prompt(t_env *env);

#endif
