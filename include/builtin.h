/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:22:28 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/28 18:36:48 by rde-mour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "ast.h"
# include "expansions.h"

int	builtin_exit(t_env *env, t_ast **ast, char **cmd, int *fds);

#endif
