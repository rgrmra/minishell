/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:22:24 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/14 22:45:37 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <fcntl.h>
#include "ft_stdlib.h"
#include "ft_string.h"

static char	*get_filename(void)
{
	static int	count;
	char		*filename;
	char		*tmp;

	tmp = ft_itoa(count++);
	filename = ft_strjoin("/var/tmp/minishell-private-tmp_", tmp);
	free(tmp);
	return (filename);
}

char	*heredoc(char *limiter)
{
	char	*filename;
	char	*input;
	int		fd;

	fd = -1;
	while (fd == -1)
	{
		filename = get_filename();
		fd = open(filename, O_CREAT | O_RDWR | O_EXCL, S_IRUSR | S_IWUSR);
		if (fd == -1)
			free(filename);
	}
	while (1)
	{
		input = readline("> ");
		if (!input || ft_strncmp(limiter, input, ft_strlen(limiter) + 1) == 0)
			break ;
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	close(fd);
	if (input)
		free(input);
	return (filename);
}
