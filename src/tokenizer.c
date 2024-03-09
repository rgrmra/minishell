/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:51:23 by rde-mour          #+#    #+#             */
/*   Updated: 2024/03/09 16:43:06 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include "ft_linkedlist.h"
#include "ft_string.h"
#include "tokens.h"
#include <stdlib.h>

int	get_token(char *string, int last_token)
{
	if (ft_strncmp(string, "|", 2))
		return (PIPE);
	else if (ft_strncmp(string, "<<", 3))
		return (HEREDOC);
	else if (ft_strncmp(string, "<", 2))
		return (LEFT_REDIRECT);
	else if (ft_strncmp(string, ">>", 3))
		return (APPEND);
	else if (ft_strncmp(string, ">", 2))
		return (RIGHT_REDIRECT);
	else if (*string == '\"')
		return (DOUBLE_QUOTE);
	else if (*string == '\'')
		return (QUOTE);
	else if (ft_isalpha(*string) && last_token < 8)
		return (COMMAND);
	return (SYNTAX);
}

void	check_token(t_list **tokens, char *string)
{
	t_content	*content;
	int			last_token;

	if (!string)
		return ;
	content = (t_content *) malloc(sizeof(t_content));
	if (!content)
		return ;
	content->string = string;
	last_token = 0;
	//if (tokens)
	//	last_token = (ft_lstlast(*tokens)->content)->token;
	content->token = get_token(string, last_token);
	ft_lstadd_back(tokens, (void *) content);
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
	return (tokens);
}
