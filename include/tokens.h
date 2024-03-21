/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/20 19:27:10 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "ft_linkedlist.h"

typedef struct s_content	t_content;

struct s_content
{
	char	*string;
	int		token;
};

enum	e_token
{
	INVALID = 1 << 0,
	COMMAND = 1 << 1,
	FLAG = 1 << 2,
	PIPE = 1 << 3,
	LEFT_REDIRECT = 1 << 4,
	HEREDOC = 1 << 5,
	RIGHT_REDIRECT = 1 << 6,
	APPEND = 1 << 7,
	PUT_FILE = 1 << 8,
	HEREDOC_FILE = 1 << 9,
	LIMITER = 1 << 10,
	AND_IF = 1 << 11,
	OR_IF = 1 << 12,
	SUB_IN = 1 << 13,
	SUB_OUT = 1 << 14
};

void	token_clear(void *content);
t_list	*tokenizer(char **splitted);

#endif
