/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/18 10:35:24 by rde-mour         ###   ########.org.br   */
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
	PIPE = 6,
	LEFT_REDIRECT = 8,
	HEREDOC = 10,
	RIGHT_REDIRECT = 12,
	APPEND = 14,
	PUT_FILE = 16,
	HEREDOC_FILE = 18,
	LIMITER = 20,
	AND_IF = 22,
	OR_IF = 24,
	SUB_IN = 26,
	SUB_OUT = 28
};

t_list	*tokenizer(char **splitted);

#endif
