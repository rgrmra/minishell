/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/18 11:42:57 by rde-mour         ###   ########.org.br   */
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
	INVALID = 0,
	COMMAND = 2,
	FLAG = 4,
	PIPE = 8,
	LEFT_REDIRECT = 16,
	HEREDOC = 32,
	RIGHT_REDIRECT = 64,
	APPEND = 128,
	PUT_FILE = 256,
	HEREDOC_FILE = 512,
	LIMITER = 1024,
	AND_IF = 2048,
	OR_IF = 4096,
	SUB_IN = 8192,
	SUB_OUT = 16384
};

void	token_clear(void *content);
t_list	*tokenizer(char **splitted);

#endif
