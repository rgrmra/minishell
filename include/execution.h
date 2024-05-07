/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:07:26 by rde-mour          #+#    #+#             */
/*   Updated: 2024/05/05 21:00:50 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "ast.h"
# include "expansions.h"

void	closeall(int *fds);
void	clearall(t_env *env);
void	execute_command(t_env *env, t_ast *ast, int *fds);
void	execute_pipe(t_env *env, t_ast *ast);
void	execute_redirection(t_env *env, t_ast *ast);
void	execute_subshell(t_env *env, t_ast *ast);
void	execute_conditional(t_env *env, t_ast *ast);
void	execute(t_env *env, t_ast *ast, int *fds);
void	panic(char *cmd, char *flag, char *message, int error);

#endif
