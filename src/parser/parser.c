/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 07:41:33 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/01 19:25:16 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_linkedlist.h"
#include "tokenizer.h"
#include "types.h"

static int	check_invalid(t_token *content)
{
	if (content->type & (ILLEGAL))
		return (true);
	return (false);
}

static int	check_controllers(t_token *content, t_list *next_content)
{
	t_token	*next;

	if (!next_content && content->type & (AND | OR))
		return (true);
	if (!next_content)
		return (false);
	next = next_content->content;
	if (content->type & (AND | OR) && next->type & (AND | OR
			| VBAR | RPAREN))
		return (true);
	if (content->type & (AND | OR | VBAR | LESS | DLESS
			| GREATER | DGREATER | LPAREN) && next->type & (AND
			| OR))
		return (true);
	if (content->type & (RPAREN) && next->type & (LPAREN))
		return (true);
	if (content->type & (RPAREN) && next->type & (COMMAND))
		return (true);
	return (false);
}

static int	check_operators(t_token *content, t_list *next_content)
{
	t_token	*next;

	if (!next_content && content->type & (VBAR | LESS | DLESS
			| GREATER | DGREATER | LPAREN))
		return (true);
	if (!next_content)
		return (false);
	next = next_content->content;
	if (content->type & (LESS | DLESS | GREATER
			| DGREATER) && next->type & (LESS | DLESS
			| GREATER | DGREATER | RPAREN))
		return (true);
	if (content->type & VBAR && next->type & (VBAR | RPAREN))
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
	if (((t_token *) tmp->content)->type & (VBAR | AND | OR | RPAREN)
		&& error(true, tokens, ((t_token *) tmp->content)->literal))
		return ;
	while (tmp)
	{
		errors += check_invalid((t_token *) tmp->content);
		if (error(errors, tokens, ((t_token *) tmp->content)->literal))
			return ;
		errors += check_controllers((t_token *) tmp->content, tmp->next);
		if (error(errors, tokens, ((t_token *) tmp->content)->literal))
			return ;
		errors += check_operators((t_token *) tmp->content, tmp->next);
		if ((tmp->next && error(errors, tokens,
					((t_token *) tmp->next->content)->literal))
			|| error(errors, tokens, ((t_token *) tmp->content)->literal))
			return ;
		tmp = tmp->next;
	}
}
