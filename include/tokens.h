/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:22:53 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/09 16:17:16 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef struct s_content	t_content;

struct s_content
{
	char *	string;
	int		token;
};

enum	e_token
{
	SYNTAX,
	QUOTE,
	DOUBLE_QUOTE,
	PIPE,
	LEFT_REDIRECT,
	HEREDOC,
	RIGHT_REDIRECT,
	APPEND,
	COMMAND,
	FLAG
};

#endif
