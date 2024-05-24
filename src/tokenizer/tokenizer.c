/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:51:23 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/22 06:57:00 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "ft_stdio.h"
#include "prompt.h"
#include "parser.h"
#include "types.h"
#include "builtin.h"
#include "ft_linkedlist.h"
#include "ft_string.h"
#include "tokenizer.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
		exit_error("malloc", EXIT_FAILURE);
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

static t_list	*clear_error(t_list **tokens, char **splitted, int i)
{
	ft_lstclear(tokens, token_clear);
	while (*(splitted + i))
		free(*(splitted + i++));
	return (NULL);
}

t_list	*tokenizer(char **splitted)
{
	t_env	*env;
	t_list	*tokens;
	int		i;

	if (!splitted)
		return (NULL);
	i = 0;
	tokens = NULL;
	env = tenv(NULL);
	while (*(splitted + i))
	{
		if (!find_quote(*(splitted + i)))
			env->execute = true;
		else if (!check_token(&tokens, *(splitted + i)))
		{
			ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
			g_status = 2;
			env->execute = true;
		}
		if (env->execute)
			return (clear_error(&tokens, splitted, i));
		i++;
	}
	tokens = append_commands(tokens);
	return (parser(&tokens), tokens);
}
