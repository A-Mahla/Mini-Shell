/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_action_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:47:27 by meudier           #+#    #+#             */
/*   Updated: 2022/07/21 15:31:40 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	g_sigint_code = 0;

int	no_leaks2(t_vars *vars, t_parser *parser, t_parser *new)
{
	lst_clear_parser(new);
	if (vars->pipe_info->pipes)
		close_pipes(vars->pipe_info);
	close(0);
	close(1);
	close(2);
	if (parser)
	{
		close_std(parser);
		lst_clear_parser(parser);
	}
	lst_clear_lexer(vars->lst_lexer);
	lst_clear_envl(vars->envl);
	lst_clear_envl(vars->var);
	clear_history();
	exit(0);
}

void	handler_herdoc(int sig)
{
	(void)sig;
	close(0);
	g_sigint_code = 1;
	write(1, "\n", 1);
}

void	heredoc_child(int fds[2], t_vars *vars, char *limiter)
{
	char	*line;

	close(fds[0]);
	signal(SIGINT, &handler_herdoc);
	while (1 && !g_sigint_code)
	{
		line = readline("> ");
		if (!line)
		{
			write(2, "minishell: warning: here-document at line 1 ", 44);
			write(2, "delimited by end-of-file (wanted `eof')\n", 40);
			break ;
		}
		ft_expand(&line, vars, vars->lst_lexer);
		if (ft_strcmp(line, limiter) == 0 || g_sigint_code)
			break ;
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	g_sigint_code = 0;
	close(fds[1]);
	free(line);
}

int	open_heredoc(char *limiter, t_vars *vars, t_parser *parser, t_parser *new)
{
	int		fds[2];
	int		pid;

	if (pipe(fds) == -1)
		return (-1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{		
		heredoc_child(fds, vars, limiter);
		no_leaks2(vars, parser, new);
	}
	wait(NULL);
	close(fds[1]);
	return (fds[0]);
}

int	heredoc(t_parser **new, t_lexer **lexer, t_vars *vars,
t_parser *parser)
{
	t_in	*last_in;

	push_in(&((*new)->stdin), open_heredoc((*lexer)->next->data, \
	vars, parser, *new), vars);
	last_in = (*new)->stdin;
	while (last_in->next)
		last_in = last_in->next;
	if (last_in->stdin < 0)
	{
		perror((*lexer)->next->data);
		return (0);
	}
	(*lexer) = (*lexer)->next->next;
	return (1);
}
