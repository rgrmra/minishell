/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/22 10:40:04 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "ft_linkedlist.h"

typedef struct s_content	t_content;

struct s_content
{
	char	*string;
	int		token;
};

enum	e_tokens
{
	INVALID = 1 << 0,
	COMMAND = 1 << 1,
	PIPE = 1 << 2,
	LEFT_REDIRECT = 1 << 3,
	HEREDOC = 1 << 4,
	RIGHT_REDIRECT = 1 << 5,
	APPEND = 1 << 6,
	PUT_FILE = 1 << 7,
	LIMITER = 1 << 8,
	AND_IF = 1 << 9,
	OR_IF = 1 << 10,
	SUB_IN = 1 << 11,
	SUB_OUT = 1 << 12
};

void	token_clear(void *content);
t_list	*tokenizer(char **splitted);
t_list	*append_commands(t_list *tokens);

#endif
