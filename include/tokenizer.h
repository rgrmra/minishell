/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/19 20:28:48 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "ft_linkedlist.h"

enum					e_token_type
{
	ILLEGAL = 1 << 0,
	COMMAND = 1 << 1,
	FILENAME = 1 << 2,
	LESS = 1 << 3,
	GREATER = 1 << 4,
	DLESS = 1 << 5,
	DGREATER = 1 << 6,
	VBAR = 1 << 7,
	AND = 1 << 8,
	OR = 1 << 9,
	PAREN = 1 << 10,
	END = 1 << 11,
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*literal;
}						t_token;

void					token_clear(void *content);
t_list					*tokenizer(char **splitted);
t_list					*append_commands(t_list *tokens);
void					invert_commands(t_list *tokens);

#endif
