/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 07:41:33 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 18:38:08 by rde-mour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linkedlist.h"
#include "tokenizer.h"
#include "types.h"
#include <stdio.h>

static int	check_controllers(t_token *content, t_list *next_content)
{
	t_token	*next;

	if (content->type & (ILLEGAL))
		return (true);
	if (!next_content && content->type & (AND | OR))
		return (true);
	if (!next_content)
		return (false);
	next = next_content->content;
	if (content->type & (AND | OR) && next->type & (AND | OR | VBAR))
		return (true);
	if (content->type & (AND | OR | VBAR | LESS | DLESS | GREATER | DGREATER)
		&& next->type & (AND | OR))
		return (true);
	if (content->type & PAREN && next->type & PAREN)
		return (true);
	if ((content->type & (PAREN) && next->type & (COMMAND))
		|| (content->type & (COMMAND) && next->type & (PAREN)))
		return (true);
	return (false);
}

static int	check_operators(t_token *content, t_list *next_content)
{
	t_token	*next;

	if (!next_content
		&& content->type & (VBAR | LESS | DLESS | GREATER | DGREATER))
		return (true);
	if (!next_content)
		return (false);
	next = next_content->content;
	if (content->type & (LESS | DLESS | GREATER | DGREATER)
		&& next->type & (LESS | DLESS | GREATER | DGREATER | PAREN))
		return (true);
	if (content->type & VBAR && next->type & VBAR)
		return (true);
	if (content->type & FILENAME && next->type & PAREN)
		return (true);
	return (false);
}

int	error(int errors, t_list **tokens, char *message)
{
	if (errors)
	{
		printf("minishell: syntax error near type '%s'\n", message);
		ft_lstclear(tokens, &token_clear);
		return (true);
	}
	return (false);
}

void	parser(t_list **tokens)
{
	int		errors;
	t_list	*tmp;

	if (!tokens || !(*tokens))
		return ;
	errors = 0;
	tmp = *tokens;
	if (((t_token *)tmp->content)->type & (VBAR | AND | OR) && error(true,
			tokens, ((t_token *)tmp->content)->literal))
		return ;
	while (tmp)
	{
		errors += check_controllers((t_token *)tmp->content, tmp->next);
		if (error(errors, tokens, ((t_token *)tmp->content)->literal))
			return ;
		errors += check_operators((t_token *)tmp->content, tmp->next);
		if ((tmp->next && error(errors, tokens,
					((t_token *)tmp->next->content)->literal)) || error(errors,
				tokens, ((t_token *)tmp->content)->literal))
			return ;
		tmp = tmp->next;
	}
	invert_commands(*tokens);
}
