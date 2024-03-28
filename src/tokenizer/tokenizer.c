/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:51:23 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/28 09:40:36 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linkedlist.h"
#include "ft_string.h"
#include "tokenizer.h"
#include <stdlib.h>
#include <stdio.h>

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
	else if (!ft_strncmp(literal, "(", 2))
		return (LPAREN);
	else if (!ft_strncmp(literal, ")", 2))
		return (RPAREN);
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
	int			last_token;

	if (!literal)
		return (0);
	content = (t_token *) malloc(1 * sizeof(t_token));
	if (!content)
		return (0);
	content->literal = literal;
	last_token = 0;
	if (*tokens)
		last_token = ((t_token *) ft_lstlast(*tokens)->content)->type;
	content->type = get_token(literal, last_token);
	ft_lstaddcontent_back(tokens, (void *) content);
	if (content->type & LPAREN)
		return (1);
	else if (content->type & RPAREN)
		return (-1);
	return (0);
}

void	token_clear(void *content)
{
	free(((t_token *) content)->literal);
	free(content);
}

t_list	*tokenizer(char **splitted)
{
	t_list	*tokens;
	int		parentesis;
	int		i;

	if (!splitted)
		return (NULL);
	i = 0;
	parentesis = 0;
	tokens = NULL;
	while (*(splitted + i))
	{
		parentesis += check_token(&tokens, *(splitted + i++));
		if (parentesis < 0)
			parentesis--;
	}
	if (parentesis == 0)
		return (append_commands(tokens));
	ft_lstclear(&tokens, &token_clear);
	if (parentesis > 0)
		printf("%s %c\n", "unclosed parentesis parser error", '(');
	if (parentesis < 0)
		printf("%s %c\n", "unclosed parentesis parser error", ')');
	return (NULL);
}
