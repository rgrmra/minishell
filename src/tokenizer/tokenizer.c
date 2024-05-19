/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:51:23 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/19 15:46:35 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "prompt.h"
#include "parser.h"
#include "builtin.h"
#include "ft_linkedlist.h"
#include "ft_string.h"
#include "tokenizer.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

extern volatile sig_atomic_t	g_status;

static int	get_token(char *literal, int last_token)
{
	if (!ft_strncmp(literal, "|", 2))
		return (VBAR);
	else if (!ft_strncmp(literal, "||", 3))
		return (OR);
	else if (!ft_strncmp(literal, "&&", 3))
		return (AND);
	else if (!ft_strncmp(literal, "<<", 3))
		return (DLESS);
	else if (!ft_strncmp(literal, "<", 2))
		return (LESS);
	else if (!ft_strncmp(literal, ">>", 3))
		return (DGREATER);
	else if (!ft_strncmp(literal, ">", 2))
		return (GREATER);
	else if (!ft_strncmp(literal, "(", 1))
		return (PAREN);
	else if (ft_strchr("()|<>&", *literal))
		return (ILLEGAL);
	else if (last_token & DLESS)
		return (END);
	else if (last_token & (DLESS | LESS | DGREATER | GREATER))
		return (FILENAME);
	return (COMMAND);
}

static int	check_token(t_list **tokens, char *literal)
{
	t_token	*content;
	t_list	*last;
	int		last_token;

	if (!literal)
		return (ILLEGAL);
	content = (t_token *)malloc(1 * sizeof(t_token));
	if (!content)
		return (ILLEGAL);
	content->literal = literal;
	last_token = 0;
	last = ft_lstlast(*tokens);
	if (*tokens)
		last_token = ((t_token *)last->content)->type;
	content->type = get_token(literal, last_token);
	if (content->type & END)
		heredoc(&content->literal);
	ft_lstaddcontent_back(tokens, (void *)content);
	return (content->type);
}

void	token_clear(void *content)
{
	free(((t_token *)content)->literal);
	free(content);
}

t_list	*tokenizer(char **splitted)
{
	t_list	*tokens;
	int		i;

	if (!splitted)
		return (NULL);
	i = 0;
	tokens = NULL;
	while (*(splitted + i))
	{
		if (!find_quote(*(splitted + i)))
		{
			ft_lstclear(&tokens, token_clear);
			while (*(splitted + i))
				free(*(splitted + i++));
			return (NULL);
		}
		if (!check_token(&tokens, *(splitted + i)))
		{
			ft_putstr("minishell: syntax error near type '");
			ft_putstr(*(splitted + i));
			ft_putstr("'\n");
			g_status = 2;
			ft_lstclear(&tokens, token_clear);
			while (*(splitted + i))
				free(*(splitted + i++));
			return (NULL);
		}
		i++;
	}
	tokens = append_commands(tokens);
	parser(&tokens);
	return (tokens);
}
