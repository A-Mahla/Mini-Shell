/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:39:27 by meudier           #+#    #+#             */
/*   Updated: 2022/07/04 11:34:06 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	get_num_of_process(t_lexer *lexer)
{
	t_lexer	*lst;
	int		count;

	count = 1;
	lst = lexer;
	while (lst)
	{
		if (lst->type == PIPE)
			count++;
		lst = lst->next;
	}
	return (count);
}

int	**free_if_pipes(int num_of_process, int **pipes)
{
	if (num_of_process == 1)
		free(pipes);
	return (0);
}

int	**get_pipes(t_lexer *lexer, int *num_of_process)
{
	int	i;
	int	**pipes;

	*num_of_process = get_num_of_process(lexer);
	pipes = (int **)calloc(sizeof(int *), (*num_of_process));
	if (!pipes || *num_of_process == 1)
		return (free_if_pipes(*num_of_process, pipes));
	i = 0;
	while (i < *num_of_process)
	{
		pipes[i] = (int *)calloc(sizeof(int), 2);
		if (!pipes[i])
			exit (1);
		i++;
	}
	i = 0;
	while (i < *num_of_process)
	{
		if (pipe(pipes[i]) == -1)
			exit (2);
		i++;
	}
	return (pipes);
}

int	is_not_a_pipe(int fd, int **pipes, int num_of_process)
{
	int	i;

	i = 0;
	while (pipes && i < num_of_process)
	{
		if (fd == pipes[i][0] || fd == pipes[i][1])
			return (0);
		i++;
	}
	return (1);
}
