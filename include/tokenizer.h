/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/08 13:09:06 by rde-mour         ###   ########.org.br   */
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
	PAREN = 1 << 8,
	FILENAME = 1 << 9,
	COMMAND = 1 << 10,
	END = 1 << 11,
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*literal;
}	t_token;

void	token_clear(void *content);
t_list	*tokenizer(char **splitted);
t_list	*append_commands(t_list *tokens);
void	invert_commands(t_list *tokens);

#endif
