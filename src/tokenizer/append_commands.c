/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:55:34 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/22 10:48:39 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "strjoinsep.h"

static void	append(t_list *tmp, t_list *next)
{
	char	*string;

	string = strjoinsep(((t_content *) tmp->content)->string,
			((t_content *) next->content)->string, ' ');
	free(((t_content *) tmp->content)->string);
	((t_content *) tmp->content)->string = string;
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
		if (((t_content *) tmp->content)->token & COMMAND
			&& ((t_content *) next->content)->token & COMMAND)
			append(tmp, next);
		else if (((t_content *) tmp->content)->token & COMMAND
			&& ((t_content *) next->content)->token & (HEREDOC | LEFT_REDIRECT
				| APPEND | RIGHT_REDIRECT) && next->next && next->next->next
			&& ((t_content *) next->next->content)->token & (PUT_FILE | LIMITER)
			&& ((t_content *) next->next->next->content)->token & COMMAND)
			swap_flags(tmp, next, next->next->next);
		else
			tmp = tmp->next;
	}
	return (tokens);
}
