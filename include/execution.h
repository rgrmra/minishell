/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:07:26 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/01 22:12:18 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "ast.h"
# include "expansions.h"

int		*alloc_fds(void);
void	closeall(int *fds);
void	execute_command(t_env *env, t_ast **ast, int *fds);
void	execute_pipe(t_env *env, t_ast **ast, int *lfds);
void	execute_redirection(t_env *env, t_ast **ast, int *lfds);
void	execute_subshell(t_env *env, t_ast **ast, int *lfds);
void	execute_condition(t_env *env, t_ast **ast, int *fds);
void	execute(t_env *env, t_ast **ast, int *fds);

#endif
