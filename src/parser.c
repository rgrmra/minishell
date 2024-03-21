/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 07:41:33 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/21 11:38:36 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_linkedlist.h"
#include "tokens.h"
#include "types.h"

static int	check_invalid(t_content *content)
{
	if (content->token & (INVALID))
		return (true);
	return (false);
}

static int	check_controllers(t_content *content, t_list *next_content)
{
	t_content	*next;

	if (!next_content && content->token & (AND_IF | OR_IF))
		return (true);
	if (!next_content)
		return (false);
	next = next_content->content;
	if (content->token & (AND_IF | OR_IF) && next->token & (AND_IF | OR_IF
			| PIPE | LEFT_REDIRECT | HEREDOC | RIGHT_REDIRECT | APPEND
			| SUB_OUT))
		return (true);
	if (content->token & (AND_IF | OR_IF | PIPE | LEFT_REDIRECT | HEREDOC
			| RIGHT_REDIRECT | APPEND | SUB_IN) && next->token & (AND_IF
			| OR_IF))
		return (true);
	return (false);
}

static int	check_operators(t_content *content, t_list *next_content)
{
	t_content	*next;

	if (!next_content && content->token & (PIPE | LEFT_REDIRECT | HEREDOC
			| RIGHT_REDIRECT | APPEND | SUB_IN))
		return (true);
	if (!next_content)
		return (false);
	next = next_content->content;
	if (content->token & (PIPE | LEFT_REDIRECT | HEREDOC | RIGHT_REDIRECT
			| APPEND) && next->token & (PIPE | LEFT_REDIRECT | HEREDOC
			| RIGHT_REDIRECT | APPEND | SUB_IN | SUB_OUT))
		return (true);
	return (false);
}

int	error(int errors, t_list **tokens, char *message)
{
	if (errors)
	{
		printf("minishell: syntax error near token '%s'\n", message);
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
	while (tmp)
	{
		errors += check_invalid((t_content *) tmp->content);
		if (error(errors, tokens, ((t_content *) tmp->content)->string))
			return ;
		errors += check_controllers((t_content *) tmp->content, tmp->next);
		if (error(errors, tokens, ((t_content *) tmp->content)->string))
			return ;
		errors += check_operators((t_content *) tmp->content, tmp->next);
		if ((tmp->next && error(errors, tokens,
			((t_content *) tmp->next->content)->string))
			|| error(errors, tokens, ((t_content *) tmp->content)->string))
			return ;
		tmp = tmp->next;
	}
}
