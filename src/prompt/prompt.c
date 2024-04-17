/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:00:16 by rde-mour          #+#    #+#             */
/*   Updated: 2024/04/16 21:34:17 by rde-mour         ###   ########.org.br   */
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

static void	execute_command(t_env *env, t_ast **ast, int *lfd)
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
		rl_clear_history();
		if (lfd)
		{
			lfd[2] = open("file", O_TRUNC | O_CREAT | O_RDWR, 0644);
			dup2(lfd[0], STDOUT_FILENO);
			close(lfd[0]);
			close(lfd[1]);
			dup2(lfd[2], STDIN_FILENO);
			close(lfd[2]);
		}
		if (*cmd && (ft_strchr("./", **cmd) || access(*cmd, F_OK | X_OK) == 0)
			&& execve(*cmd, cmd, env->environ) < 0)
			(printf("failed\n"), exit(EXIT_FAILURE));
		printf("command not found!\n");
		ft_memclear((void **) cmd, &free);
		exit(EXIT_FAILURE);
	}
	ft_memclear((void **) cmd, &free);
	waitpid(pid, NULL, WUNTRACED);
}

static void	execute_open(t_env *env, t_ast **ast)
{
	pid_t	pid;
	t_ast	*tmp;
	int	fd[3];

	tmp = *ast;
	var_expansions(env, tmp->left->content);
	remove_quotes_aux(tmp->left->content->literal);
	pid = fork();
	pipe(fd);
	if (pid == 0)
	{
		rl_clear_history();
		fd[2] = open(tmp->left->content->literal, O_RDONLY, 0644);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		dup2(fd[2], STDIN_FILENO);
		close(fd[2]);
		execute_command(env, &((*ast)->right), fd);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, WUNTRACED);
}

static void	execute(t_env *env, t_ast **ast)
{
	if (!ast || !(*ast))
		return ;
	if ((*ast)->content->type & COMMAND)
		execute_command(env, ast, NULL);
	else if ((*ast)->content->type & (LESS | DLESS))
		execute_open(env, ast);
	else if ((*ast)->content->type & GREATER)
		printf("Open output file %s\n", (*ast)->content->literal);
	else if ((*ast)->content->type & DGREATER)
		printf("Open append output file %s\n", (*ast)->content->literal);
	else if ((*ast)->content->type & VBAR)
		printf("Open pipeline %s\n", (*ast)->content->literal);
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
	execute(env, &ast);
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
