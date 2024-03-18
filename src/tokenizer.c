/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:51:23 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/17 21:14:12 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linkedlist.h"
#include "ft_string.h"
#include "tokens.h"
#include <stdlib.h>
#include <stdio.h>

static int	get_token(char *string, int last_token)
{
	if (!ft_strncmp(string, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(string, "||", 3))
		return (OR_IF);
	else if (!ft_strncmp(string, "&&", 3))
		return (AND_IF);
	else if (!ft_strncmp(string, "<<", 3))
		return (HEREDOC);
	else if (!ft_strncmp(string, "<", 2))
		return (LEFT_REDIRECT);
	else if (!ft_strncmp(string, ">>", 3))
		return (APPEND);
	else if (!ft_strncmp(string, ">", 2))
		return (RIGHT_REDIRECT);
	else if (!ft_strncmp(string, "(", 2))
		return (SUB_IN);
	else if (!ft_strncmp(string, ")", 2))
		return (SUB_OUT);
	else if (ft_strchr("()|<>&", *string))
		return (INVALID);
	else if (last_token == HEREDOC)
		return (HEREDOC_FILE);
	else if (last_token == HEREDOC_FILE)
		return (LIMITER);
	else if (last_token >= 4 && last_token <= 7)
		return (PUT_FILE);
	else if (last_token == COMMAND || last_token == FLAG)
		return (FLAG);
	return (COMMAND);
}

static int	check_token(t_list **tokens, char *string)
{
	t_content	*last_content;
	t_content	*content;
	int			last_token;

	if (!string)
		return (0);
	content = (t_content *) malloc(1 * sizeof(t_content));
	if (!content)
		return (0);
	content->string = string;
	last_token = 0;
	if (*tokens)
	{
		last_content = ft_lstlast(*tokens)->content;
		last_token = last_content->token;
	}
	content->token = get_token(string, last_token);
	ft_lstaddcontent_back(tokens, (void *) content);
	if (content->token == SUB_IN)
		return (1);
	else if (content->token == SUB_OUT)
		return (-1);
	return (0);
}

static void	token_clear(void *content)
{
	free(((t_content *) content)->string);
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
		parentesis += check_token(&tokens, *(splitted + i++));
	if (parentesis == 0)
		return (tokens);
	ft_lstclear(&tokens, &token_clear);
	if (parentesis > 0)
		printf("%s %c\n", "unclosed parentesis parser error", ')');
	if (parentesis < 0)
		printf("%s %c\n", "unclosed parentesis parser error", '(');
	return (0);
}
