/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/09 21:53:43 by rde-mour         ###   ########.org.br   */
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
};

t_list	*tokenizer(char **splitted);

#endif
