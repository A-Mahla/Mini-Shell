/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_action_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:47:27 by meudier           #+#    #+#             */
/*   Updated: 2022/07/19 15:43:32 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	g_sigint_code = 0;

void	handler_herdoc(int sig)
{
	(void)sig;
	close(0);
	g_sigint_code = 1;
	write(1, "\n", 1);
}

int	open_heredoc(char *limiter, t_vars *vars)
{
	int		fds[2];
	char	*line;
	int		pid;

	if (pipe(fds) == -1)
		return (-1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{		
		close(fds[0]);
		signal(SIGINT, &handler_herdoc);
		while (1 && !g_sigint_code)
		{
			line = readline("> ");
			ft_expand(&line, vars, vars->lst_lexer);
			if (ft_strcmp(line, limiter) == 0 || g_sigint_code)
				break ;
			write(fds[1], line, ft_strlen(line));
			write(fds[1], "\n", 1);
			free(line);
		}
		g_sigint_code = 0;
		close (fds[1]);
		free(line);
		exit (0);
	}
	wait(NULL);
	close(fds[1]);
	return (fds[0]);
}

void	heredoc(t_parser **new, t_lexer **lexer, t_vars *vars)
{
	t_in	*last_in;

	push_in(&((*new)->stdin), open_heredoc((*lexer)->next->data, vars), vars);
	last_in = (*new)->stdin;
	while (last_in->next)
		last_in = last_in->next;
	if (last_in->stdin < 0)
		perror((*lexer)->next->data);
	(*lexer) = (*lexer)->next->next;
}
