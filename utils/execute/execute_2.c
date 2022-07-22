/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:54:06 by ammah             #+#    #+#             */
/*   Updated: 2022/07/21 08:16:41 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	get_last_pid(int *pids)
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
				write(2, "Quit: (core dumped)\n", 20);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
		}
		i++;
	}
}

int	is_not_slashbar(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/' || cmd[i] == '.')
			return (0);
		i++;
	}
	return (1);
}

int	no_leaks(int *pids, char *cmd_path, t_vars *vars, int built)
{
	free(pids);
	if (cmd_path || is_not_slashbar(vars->lst_parser->cmd))
		free(cmd_path);
	if (vars->pipe_info->pipes)
		close_pipes(vars->pipe_info);
	close(0);
	close(1);
	close(2);
	close_std(vars->lst_parser);
	lst_clear_parser(vars->lst_parser);
	lst_clear_lexer(vars->lst_lexer);
	lst_clear_envl(vars->envl);
	lst_clear_envl(vars->var);
	clear_history();
	if (built)
		exit(vars->exit_code);
	exit(1);
}

void	dup_and_close(t_parser *parser, int built, int *pids, t_vars *vars)
{
	if (!built && !dup_fd(parser))
		exit(no_leaks(pids, NULL, vars, 0));
	close_pipes(vars->pipe_info);
}
