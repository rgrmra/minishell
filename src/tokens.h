/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/12 01:23:04 by rde-mour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "ft_linkedlist.h"

typedef struct s_content	t_content;

typedef enum e_token
{
	INVALID,
	COMMAND,
	FLAG,
	QUOTE,
	DOUBLE_QUOTE,
	PIPE,
	LEFT_REDIRECT,
	HEREDOC,
	RIGHT_REDIRECT,
	APPEND,
	PUT_FILE,
	HEREDOC_FILE,
	LIMITER
}							t_token;

struct						s_content
{
	t_token					token;
	char					*literal;
};

t_list						*tokenizer(char **splitted);

#endif
