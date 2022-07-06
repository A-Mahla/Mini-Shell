/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:13:40 by maxenceeudi       #+#    #+#             */
/*   Updated: 2022/07/04 10:55:52 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	close_std(t_parser *parser)
{
	t_parser	*last;
	t_in		*last_in;

	last = parser;
	while (last)
	{
		if (last->stdout != 1)
			close(last->stdout);
		last_in = last->stdin;
		while (last_in)
		{
			if (last_in->stdin != 0)
				close (last_in->stdin);
			last_in = last_in->next;
		}
		last = last->next;
	}
}

int	free_tab_int(int **tab, int size)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (i < size)
		free (tab[i++]);
	free(tab);
	return (0);
}

void	close_pipes(t_pipe_info *pipe_info)
{
	int	i;

	i = 0;
	while (pipe_info->pipes && i < pipe_info->num_of_process)
	{
		close(pipe_info->pipes[i][0]);
		close(pipe_info->pipes[i][1]);
		free(pipe_info->pipes[i]);
		i++;
	}
	free(pipe_info->pipes);
	pipe_info->pipes = NULL;
}
