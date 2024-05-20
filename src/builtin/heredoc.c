/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:22:24 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/19 21:34:04 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "types.h"
#include "prompt.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "get_env.h"

extern volatile sig_atomic_t	g_status;
static char	*get_filename(void)
{
	static int	count = 100;
	char		*filename;
	char		*tmp;

	tmp = ft_itoa(count++);
	filename = ft_strjoin("/var/tmp/minishell-private-tmp-", tmp);
	free(tmp);
	return (filename);
}

static int	get_fd(char **filename)
{
	int	fd;

	fd = -1;
	while (fd == -1)
	{
		*filename = get_filename();
		fd = open(*filename, O_CREAT | O_RDWR | O_EXCL, S_IRUSR | S_IWUSR);
		if (fd == -1)
		{
			unlink(*filename);
			free(*filename);
		}
	}
	return (fd);
}

static int	check_expand(char *limiter)
{
	int	expand;

	expand = false;
	if (ft_strchr(limiter, '\'') == 0)
		expand = true;
	else if (ft_strchr(limiter, '\"') == 0)
		expand = true;
	return (expand);
}

static void	inner_heredoc(t_env	*env, char **limiter)
{
	char	*filename;
	char	*input;
	int		fd;
	int		expand;

	fd = get_fd(&filename);
	expand = check_expand(*limiter);
	remove_quotes_aux(*limiter);
	while (1)
	{
		input = readline("> ");
		if (!input || ft_strncmp(*limiter, input, ft_strlen(*limiter) + 1) == 0)
			break ;
		if (expand)
			var_expansions(env, &input);
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	if (input)
		free(input);
	free(*limiter);
	close(fd);
	*limiter = filename;
}

void	heredoc(char **limiter)
{
	t_env	*env;

	env = tenv(NULL);
	inner_heredoc(env, limiter);
}
