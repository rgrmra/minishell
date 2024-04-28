/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:09:24 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 18:36:57 by rde-mour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <readline/readline.h>
# include <readline/history.h>
# include "expansions.h"

char	*find_quote(char *tmp);
char	**format_input(char *input);
void	prompt(t_env *env);

#endif
