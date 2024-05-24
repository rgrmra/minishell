/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 06:21:02 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/22 07:21:54 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ARGUMENT_ERROR 2
# define MALLOC_FAILURE 3
# define TCGETATTR_FAILURE 4
# define TCSETATTR_FAILURE 5

void	exit_error(char *message, int status);

#endif
