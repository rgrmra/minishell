/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:00:16 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/21 13:33:55 by rde-mour         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "ft_linkedlist.h"
#include "tokenizer.h"
#include "types.h"
#include "ast.h"
#include "parser.h"
#include "expansions.h"
#include "prompt.h"
#include "get_env.h"

#include "ft_string.h"
#include <fcntl.h>

int	forked(int status)
{
	static int isforked;

	if (status == true)
		isforked = true;
	if (isforked)
		rl_clear_history();
	return (isforked);
}

void	rmast(t_ast **ast)
{
	if (!ast || !(*ast))
		return ;
	free((*ast)->content->literal);
	free((*ast)->content);
	free(*ast);
	*ast = NULL;
}

int *alloc_fds()
{
	int	*fds;

	fds = (int *) ft_calloc(4, sizeof(int));
	fds[2] = -2;
	fds[3] = -2;
	return (fds);
}

static void	execute(t_env *env, t_ast **ast, int *fds);

static void	open_stdout(int *fds)
{
	if (!fds)
		return ;
	if (fds[2] > -1)
	{
		dup2(fds[2], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		return ;
	}
}

//static void	open_stdin(int **fds)
//{
//	dup2(*fds[0], STDIN_FILENO);
//	close(*fds[0]);
//	close(*fds[1]);
//}

static void	closeall(int *fds)
{
	if (fds)
	{
		if (fds[0] > -1)
			close(fds[0]);
		if (fds[1] > -1)
			close(fds[1]);
		if (fds[2] > -1)
			close(fds[2]);
		if (fds[3] > -1)
			close(fds[3]);
		free(fds);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

static void	execute_command(t_env *env, t_ast **ast, int *fds)
{
	pid_t	pid;
	char	**cmd;
	t_ast	*tmp;

	if (!ast || !(*ast))
		return ;
	tmp = *ast;
	var_expansions(env, tmp->content);
	cmd = ft_split(tmp->content->literal, ' ');
	command_expansions(env, cmd);
	remove_quotes(cmd);
	rmast(ast);
	pid = fork();
	if (pid == 0)
	{
		forked(true);
		open_stdout(fds);
		if (*cmd && (ft_strchr("./", **cmd) || access(*cmd, F_OK | X_OK) == 0)
				&& execve(*cmd, cmd, env->environ) < 0)
			(printf("failed\n"), exit(EXIT_FAILURE));
		printf("command not found!\n");
		ft_memclear((void **) cmd, &free);
		envclear(&(env->vars));
		closeall(fds);
		exit(EXIT_SUCCESS);
	}
	if (fds && fds[0] > -1)
		close(fds[0]);
	if (fds && fds[1] > -1)
		close(fds[1]);
	if (fds && fds[2] > -1)
		close(fds[2]);
	if (fds && fds[3] > -1)
		close(fds[3]);
	if (fds && forked(false))
		closeall(fds);
	ft_memclear((void **) cmd, &free);
	waitpid(pid, NULL, WUNTRACED);
}

static void	execute_pipe(t_env *env, t_ast **ast)
{
	pid_t	pid;
	int		*fds = alloc_fds();
	t_ast	*left;
	t_ast	*right;

	pipe(fds);
	left = (*ast)->left;
	right = (*ast)->right;
	rmast(ast);
	pid = fork();
	if (pid == 0)
	{
		rl_clear_history();
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		execute(env, &((*ast)->left), fds);
		envclear(&(env->vars));
		ast_clear(&left);
		ast_clear(&right);
		//closeall(fds);
		free(fds);
		exit(EXIT_SUCCESS);
	}
	pid = fork();
	if (pid == 0)
	{
		rl_clear_history();
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		close(fds[1]);
		execute(env, &((*ast)->right), fds);
		envclear(&(env->vars));
		ast_clear(&right);
		ast_clear(&left);
		//closeall(fds);
		free(fds);
		exit(EXIT_SUCCESS);
	}
	close(fds[0]);
	close(fds[1]);
	free(fds);
	ast_clear(&left);
	ast_clear(&right);
	waitpid(pid, NULL, WUNTRACED);
}

static t_ast	*redirection(t_env *env, t_ast **ast, int *fdin, int *fdout)
{
	t_ast	*tmp;

	if (!ast || !(*ast))
		return (NULL);
	tmp = NULL;
	if ((*ast)->left && (*ast)->left->content->type & COMMAND)
		tmp = ((*ast)->left);
	else if ((*ast)->left && (*ast)->left->content->type & (LESS | DLESS | GREATER | DGREATER))
		tmp = redirection(env, &((*ast)->left), fdin, fdout);
	if ((*ast)->content->type & (LESS | DLESS))
	{
		if (*fdout > -1)
			close(*fdout);
		*fdout = open((*ast)->right->content->literal, O_RDONLY, 0644);
	}
	if ((*ast)->content->type & GREATER)
	{
		if (*fdin > -1)
			close(*fdin);
		*fdin = open((*ast)->right->content->literal, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	else if ((*ast)->content->type & DGREATER)
	{
		if (*fdin > -1)
			close(*fdin);
		*fdin = open((*ast)->right->content->literal, O_CREAT | O_APPEND | O_WRONLY, 0644);
	}
	if (*fdout == -1 || *fdin == -1)
		exit(EXIT_FAILURE);
	if (*fdout > -1)
		dup2(*fdout, STDIN_FILENO);
	return (tmp);
}

static void	execute_redirection(t_env *env, t_ast **ast)
{
	pid_t	pid;
	int		*fds;
	t_ast	*tmp;

	if (!ast || !(*ast))
		return ;
	fds = alloc_fds();
	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		rl_clear_history();
		tmp = redirection(env, ast, &fds[2], &fds[3]);
		execute(env, &tmp, fds);
		ast_clear(ast);
		envclear(&(env->vars));
		closeall(fds);
		free(fds);
		exit(EXIT_SUCCESS);
	}
	close(fds[0]);
	close(fds[1]);
	free(fds);
	waitpid(pid, NULL, WUNTRACED);
}

static void	execute_subshell(t_env *env, t_ast **ast)
{
	pid_t	pid;
	t_ast	*tmp;

	if (!ast || !(*ast))
		return ;
	tmp = (*ast)->left;
	rmast(ast);
	pid = fork();
	if (pid == 0)
	{
		forked(true);
		execute(env, &tmp, NULL);
		envclear(&(env->vars));
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, WUNTRACED);
	ast_clear(&tmp);
}

static void	execute(t_env *env, t_ast **ast, int *fds)
{
	if (!ast || !(*ast))
		return ;
	if ((*ast)->content->type & COMMAND)
		execute_command(env, ast, fds);
	else if ((*ast)->content->type & (LESS | DLESS | GREATER | DGREATER))
		execute_redirection(env, ast);
	else if ((*ast)->content->type & VBAR)
		execute_pipe(env, ast);
	else if ((*ast)->content->type & AND)
		printf("Check AND operator %s\n", (*ast)->content->literal);
	else if ((*ast)->content->type & OR)
		printf("check OR operator %s\n", (*ast)->content->literal);
	else if ((*ast)->content->type & PAREN)
		execute_subshell(env, ast);
}

static void	tokens(t_env *env, char **splitted)
{
	t_list	*tokens;
	t_ast	*ast;

	tokens = tokenizer(splitted);
	if (splitted)
		free(splitted);
	parser(&tokens);
	ast = ast_new(&tokens);
	execute(env, &ast, NULL);
}

void	prompt(t_env *env)
{
	char	*input;

	while (true)
	{
		input = readline("$ ");
		if (!input)
			break ;
		else if (*input != '\0')
			add_history(input);
		tokens(env, format_input(input));
		free(input);
	}
	rl_clear_history();
}
