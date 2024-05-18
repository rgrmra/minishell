/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:40:29 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/16 18:18:35 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

static int	glob(char *c, char *s);

static int	check(char *s)
{
	if (*s)
		return (-1);
	return (0);
}

static int	innerglob(char *c, char *s)
{
	int	rest;

	if (*c)
		rest = glob(c, s);
	else if (*s)
		rest = -1;
	else
		rest = 0;
	return (rest);
}

static int	glob(char *c, char *s)
{
	int		rest;
	char	*here;

	while (*c)
	{
		if (*c == '*')
		{
			here = s;
			while (*s)
				s++;
			while (s != here)
			{
				rest = innerglob(c, s);
				if (!rest)
					return (0);
				else if (rest < 0)
					return (1);
				--s;
			}
		}
		else if (*s++ != *c)
			return (1);
		c++;
	}
	return (check(s));
}

int	main(int argc, char **argv)
{
	struct dirent	*file;
	DIR				*root;

	root = opendir(".");
	while (1)
	{
		file = readdir(root);
		if (!file)
			break ;
		if (glob(argv[1], file->d_name) == 0)
			printf("%s\n", file->d_name);
	}
}
