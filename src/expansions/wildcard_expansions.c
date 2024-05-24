/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:40:29 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/23 23:49:48 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "expansions.h"
#include "ft_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

void	expand_wildcard(char **cmd, int *j, char *pattern)
{
	struct dirent	*file;
	DIR				*root;

	root = opendir(".");
	if (!root)
		exit_error("opendir", EXIT_FAILURE);
	while (1)
	{
		file = readdir(root);
		if (!file)
			break ;
		if (wildcard(pattern, file->d_name) == 0)
			if (*pattern == '.' || *file->d_name != '.')
				cmd[(*j)++] = ft_strdup(file->d_name);
	}
	closedir(root);
}

char	**copy_wildcard(char **old_cmd, int size)
{
	int		i;
	int		j;
	char	**cmd;

	cmd = (char **) malloc(sizeof(char *) * size);
	if (!cmd)
		exit_error("malloc", EXIT_FAILURE);
	i = 0;
	j = 0;
	while (old_cmd[i])
	{
		if (check_wildcard(old_cmd[i]))
			expand_wildcard(cmd, &j, old_cmd[i]);
		else
			cmd[j++] = ft_strdup(old_cmd[i]);
		i++;
	}
	if (j == 0)
		cmd[j++] = ft_strdup("");
	cmd[j] = NULL;
	ft_freesplit(old_cmd);
	return (cmd);
}

char	**wildcard_expansions(char **cmd)
{
	int				i;
	int				j;
	struct dirent	*file;
	DIR				*root;

	i = has_wildcard(cmd);
	if (!i)
		return (cmd);
	j = 0;
	root = opendir(".");
	if (!root)
		exit_error("opendir", EXIT_FAILURE);
	while (1)
	{
		file = readdir(root);
		if (!file)
			break ;
		j++;
	}
	closedir(root);
	return (copy_wildcard(cmd, i * j + 1));
}
