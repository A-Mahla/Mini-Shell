/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_action_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:47:27 by meudier           #+#    #+#             */
/*   Updated: 2022/07/11 18:40:01 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	open_heredoc(char *limiter)
{
	int		fd;
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, limiter) == 0)
			break ;
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	write(fds[1], "\n", 1);
	free(line);
	close(fds[1]);
	fd = dup(fds[0]);
	close(fds[0]);
	return (fd);
}

void	heredoc(t_parser **new, t_lexer **lexer)
{
	t_in	*last_in;

	push_in(&((*new)->stdin), open_heredoc((*lexer)->next->data));
	last_in = (*new)->stdin;
	while (last_in->next)
		last_in = last_in->next;
	if (last_in->stdin < 0)
		perror((*lexer)->next->data);
	(*lexer) = (*lexer)->next->next;
}
