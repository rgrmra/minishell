/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:22:28 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/20 20:02:33 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "expansions.h"

# define HEREDOC_MESSAGE "warning: here-document delimited by end-of-file"

char	*get_pwd(void);
int		check_flags(char **args);
void	builtin_echo(t_env *env, char **args);
void	builtin_cd(t_env *env, char **args);
void	builtin_pwd(t_env *env, char **args);
void	builtin_export(t_env *env, char **args);
void	builtin_unset(t_env *env, char **args);
void	builtin_env(t_env *env, char **args);
void	builtin_exit(t_env *env, char **args);
void	heredoc(char **limiter);

#endif
