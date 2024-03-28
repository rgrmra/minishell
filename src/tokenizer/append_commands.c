/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:55:34 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/28 09:37:56 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "strjoinsep.h"

static void	append(t_list *tmp, t_list *next)
{
	char	*literal;

	literal = strjoinsep(((t_token *) tmp->content)->literal,
			((t_token *) next->content)->literal, ' ');
	free(((t_token *) tmp->content)->literal);
	((t_token *) tmp->content)->literal = literal;
	tmp->next = next->next;
	ft_lstdelone(next, &token_clear);
}

static void	swap_flags(t_list *command, t_list *redirect, t_list *flag)
{
	command->next = flag;
	redirect->next->next = flag->next;
	flag->next = redirect;
}

t_list	*append_commands(t_list *tokens)
{
	t_list	*tmp;
	t_list	*next;

	tmp = tokens;
	while (tmp->next)
	{
		next = tmp->next;
		if (((t_token *) tmp->content)->type & COMMAND
			&& ((t_token *) next->content)->type & COMMAND)
			append(tmp, next);
		else if (((t_token *) tmp->content)->type & COMMAND
			&& ((t_token *) next->content)->type & (DLESS | LESS | DGREATER
				| GREATER) && next->next && next->next->next
			&& ((t_token *) next->next->content)->type & (FILENAME | END)
			&& ((t_token *) next->next->next->content)->type & COMMAND)
			swap_flags(tmp, next, next->next->next);
		else
			tmp = tmp->next;
	}
	return (tokens);
}
