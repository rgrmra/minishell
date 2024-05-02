/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:49:21 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/01 20:24:28 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "builtin.h"
#include "ft_string.h"
#include <stdlib.h>
#include <unistd.h>

void	builtin_exit(char **args)
{
	if (args)
		ft_freesplit(args);
	rl_clear_history();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(EXIT_SUCCESS);
}
