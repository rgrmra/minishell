/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:00:16 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/17 22:02:02 by rde-mour         ###   ########.org.br   */
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

#include "ft_string.h"
#include <fcntl.h>

static void	execute(t_env *env, t_ast **ast, int *fds);

static void	open_stdout(int **fds)
{
	dup2(*fds[1], STDOUT_FILENO);
	close(*fds[0]);
}

//static void	open_stdin(int **fds)
//{
//	dup2(*fds[0], STDIN_FILENO);
//	close(*fds[0]);
//	close(*fds[1]);
//}

static void	closeall()
{
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
	pid = fork();
	if (pid == 0)
	{
		if (fds)
			open_stdout(&fds);
		rl_clear_history();
		if (*cmd && (ft_strchr("./", **cmd) || access(*cmd, F_OK | X_OK) == 0)
				&& execve(*cmd, cmd, env->environ) < 0)
			(printf("failed\n"), exit(EXIT_FAILURE));
		printf("command not found!\n");
		ft_memclear((void **) cmd, &free);
		closeall();
		exit(EXIT_SUCCESS);
	}
	closeall();
	ft_memclear((void **) cmd, &free);
	waitpid(pid, NULL, WUNTRACED);
}

static void	execute_pipe(t_env *env, t_ast **ast)
{
	pid_t	pid;
	int		fds[4];

	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		execute(env, &((*ast)->left), fds);
		closeall();
		exit(EXIT_SUCCESS);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		close(fds[1]);
		execute(env, &((*ast)->right), fds);
		closeall();
		exit(EXIT_SUCCESS);
	}
	close(fds[0]);
	close(fds[1]);
	waitpid(pid, NULL, WCONTINUED);
}

static void	execute(t_env *env, t_ast **ast, int *fds)
{
	if (!ast || !(*ast))
		return ;
	if ((*ast)->content->type & COMMAND)
		execute_command(env, ast, fds);
	else if ((*ast)->content->type & (LESS | DLESS))
		printf("Open redirect infile %s\n", (*ast)->content->literal);
	else if ((*ast)->content->type & GREATER)
		printf("Open redirect output file %s\n", (*ast)->content->literal);
	else if ((*ast)->content->type & DGREATER)
		printf("Open append output file %s\n", (*ast)->content->literal);
	else if ((*ast)->content->type & VBAR)
		execute_pipe(env, ast);
	else if ((*ast)->content->type & AND)
		printf("Check AND operator %s\n", (*ast)->content->literal);
	else if ((*ast)->content->type & OR)
		printf("check OR operator %s\n", (*ast)->content->literal);
	else if ((*ast)->content->type & PAREN)
		printf("Open new fork %s\n", (*ast)->content->literal);
}

static void	tokens(t_env *env, char **splitted)
{
	t_list	*tokens;
	t_ast	*ast;

	tokens = tokenizer(splitted);
	if (splitted)
		free(splitted);
	parser(&tokens);
	(void)env;
	ast = ast_new(&tokens);
	execute(env, &ast, NULL);
	ast_clear(&ast);
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
