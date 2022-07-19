/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:54:06 by ammah             #+#    #+#             */
/*   Updated: 2022/07/18 18:33:49 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int		get_last_pid(int *pids)
{
	int	i;

	i = 0;
	while (pids[i + 1])
		i++;
	return (pids[i]);
}

void	return_value_child(int *pids, t_vars *vars)
{
	int	status;
	int	i;
	int	actual_pid;
	int	last_pid;

	i = 0;
	last_pid = get_last_pid(pids);
	while (pids[i])
	{
		actual_pid = waitpid(-1, &status, 0);
		if (last_pid == actual_pid)
		{
			if (WIFEXITED(status))
				vars->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				vars->exit_code = WTERMSIG(status) + 128;
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
				write(2, "Quit: 3\n", 8);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
		}
		i++;
	}
}
