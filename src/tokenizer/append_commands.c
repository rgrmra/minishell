/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:55:34 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/08 15:20:45 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer.h"
#include "utils.h"

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

//static void	swap_flags(t_list *command, t_list *redirect, t_list *flag)
//{
//	command->next = flag;
//	redirect->next->next = flag->next;
//	flag->next = redirect;
//}

void	invert_commands(t_list *tokens)
{
	t_list	*tmp;
	t_list	*prev;
	t_token	*pos;

	prev = NULL;
	tmp = tokens;
	while (tmp->next)
	{
		if (((t_token *) tmp->content)->type & (COMMAND | PAREN) && tmp->next->next
			&& ((t_token *) tmp->next->content)->type & (DLESS | LESS
				| DGREATER | GREATER | FILENAME | END) && (!prev
				|| ((t_token *) prev->content)->type & ~(DLESS | LESS
					| DGREATER | GREATER | FILENAME | END)))
		{
			pos = tmp->content;
			tmp->content = tmp->next->content;
			tmp->next->content = tmp->next->next->content;
			tmp->next->next->content = pos;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

static	void	pull_commands(t_list *tokens)
{
	short	status;
	t_list	*tmp;
	t_list	*prev;
	t_token	*pos;

	tmp = tokens;
	while (tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
		if (((t_token *) prev->content)->type & (LESS | DLESS | GREATER
				| DGREATER | FILENAME | END) && ((t_token *) tmp->content)->type
			& (COMMAND))
		{
			pos = tmp->content;
			tmp->content = prev->content;
			prev->content = pos;
		}
	}
	status = 0;
	tmp = tokens;
	while (tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
		if (((t_token *) prev->content)->type & (LESS | DLESS | GREATER
				| DGREATER | FILENAME | END) && ((t_token *) tmp->content)->type
			& (COMMAND))
		status = 1;
	}
	if (!status)
		return ;
	pull_commands(tokens);
}

t_list	*append_commands(t_list *tokens)
{
	t_list	*tmp;
	t_list	*next;

	pull_commands(tokens);
	tmp = tokens;
	while (tmp->next)
	{
		next = tmp->next;
		if (((t_token *) tmp->content)->type & COMMAND
			&& ((t_token *) next->content)->type & COMMAND)
			append(tmp, next);
		//else if (((t_token *) tmp->content)->type & COMMAND
		//	&& ((t_token *) next->content)->type & (DLESS | LESS | DGREATER
		//		| GREATER) && next->next && next->next->next
		//	&& ((t_token *) next->next->content)->type & (FILENAME | END)
		//	&& ((t_token *) next->next->next->content)->type & COMMAND)
		//	swap_flags(tmp, next, next->next->next);
		else
			tmp = tmp->next;
	}
	return (tokens);
}
