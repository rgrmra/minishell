/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:51:23 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 19:17:10 by rde-mour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linkedlist.h"
#include "ft_string.h"
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>

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

static void	check_token(t_list **tokens, char *literal)
{
	t_token	*content;
	int		last_token;

	if (!literal)
		return ;
	content = (t_token *)malloc(1 * sizeof(t_token));
	if (!content)
		return ;
	content->literal = literal;
	last_token = 0;
	if (*tokens)
		last_token = ((t_token *)ft_lstlast(*tokens)->content)->type;
	content->type = get_token(literal, last_token);
	ft_lstaddcontent_back(tokens, (void *)content);
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
		check_token(&tokens, *(splitted + i++));
	return (append_commands(tokens));
}
