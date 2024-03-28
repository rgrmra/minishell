/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/28 09:30:21 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "ft_linkedlist.h"

enum	e_token_type
{
	ILLEGAL = 1 << 0,
	LESS = 1 << 1,
	GREATER = 1 << 2,
	DLESS = 1 << 3,
	DGREATER = 1 << 4,
	VBAR = 1 << 5,
	AND = 1 << 6,
	OR = 1 << 7,
	LPAREN = 1 << 8,
	RPAREN = 1 << 9,
	FILENAME = 1 << 10,
	COMMAND = 1 << 11,
	END = 1 << 12,
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*literal;
}	t_token;

void	token_clear(void *content);
t_list	*tokenizer(char **splitted);
t_list	*append_commands(t_list *tokens);

#endif
