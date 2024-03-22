/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:09:24 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/22 09:40:15 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <readline/readline.h>
# include <readline/history.h>
# include "expansions.h"

char	**format_input(char *input);
void	prompt(t_env *env);

#endif
