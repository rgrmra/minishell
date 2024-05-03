/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:49:21 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/02 22:04:23 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "builtin.h"
#include "ft_string.h"
#include "ft_ctype.h"
#include <stdlib.h>
#include <unistd.h>



void	builtin_exit(char **args)
{
	//static int	alpha;
	int			status;
	//int			i;

	//i = 0;
	status = 0;
	//while (args[i])
	//	alpha = check_alpha(*args[i]);
	//if (ft_isalpha(*args[1]) && ft_isalpha(*args[2]))
	//{

	//}
	if (args)
		ft_freesplit(args);
	rl_clear_history();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(status);
}
