/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:55:34 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/21 11:25:01 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "append_flags.h"
#include "tokens.h"
#include "strjoinsep.h"

static void	append(t_list *tmp, t_list *del)
{
	char	*string;

	string = strjoinsep(((t_content *) tmp->content)->string,
			((t_content *) del->content)->string, ' ');
	free(((t_content *) tmp->content)->string);
	((t_content *) tmp->content)->string = string;
	tmp->next = del->next;
	ft_lstdelone(del, &token_clear);
}

static void	swap_flags(t_list *command, t_list *redirect, t_list *flag)
{
	command->next = flag;
	redirect->next->next = flag->next;
	flag->next = redirect;
	append(command, flag);
}

t_list	*append_flags(t_list *tokens)
{
	t_list	*tmp;
	t_list	*del;

	tmp = tokens;
	while (tmp->next)
	{
		del = tmp->next;
		if (((t_content *) tmp->content)->token & COMMAND
			&& ((t_content *) del->content)->token & FLAG)
			append(tmp, del);
		else if (((t_content *) tmp->content)->token & COMMAND
			&& ((t_content *) del->content)->token & (HEREDOC | LEFT_REDIRECT
				| APPEND | RIGHT_REDIRECT) && del->next && del->next->next
			&& ((t_content *) del->next->content)->token & (PUT_FILE | LIMITER)
			&& ((t_content *) del->next->next->content)->token & (COMMAND
				| FLAG))
			swap_flags(tmp, del, del->next->next);
		else
			tmp = tmp->next;
	}
	return (tokens);
}
