/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:41:17 by maxenceeudi       #+#    #+#             */
/*   Updated: 2022/07/21 08:18:51 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	init_pid(int num_of_process, int **pids)
{
	*pids = (int *)ft_calloc(sizeof(int), num_of_process + 1);
	if (!*pids)
		return (0);
	return (1);
}

int	execute_builtin_child(t_parser *parser, int *pids, t_vars *vars)
{
	int	built;

	built = 0;
	if (!parser->cmd)
	{
		vars->exit_code = 0;
		exit(no_leaks(pids, NULL, vars, built));
	}
	vars->exit_code = builtin(parser, &built, vars, 1);
	sig_init();
	signal(SIGQUIT, SIG_DFL);
	return (built);
}

void	exec_cmd(t_parser *parser, int *pids, int i, t_vars *vars)
{
	char	*cmd_path;
	int		built;
	char	**new_env;

	built = execute_builtin_child(parser, pids, vars);
	if (!built && !get_cmdpath(parser, &cmd_path, i, vars->envl))
	{
		vars->exit_code = 127;
		exit(no_leaks(pids, cmd_path, vars, 1));
	}
	dup_and_close(parser, built, pids, vars);
	if (!built)
	{
		new_env = lst_to_strs(vars->envl);
		execve(cmd_path, parser->arg, new_env);
		clear_tab(new_env);
		if (is_not_slashbar(parser->cmd))
			write_error(parser->cmd);
		else
			write_is_a_directory(parser->cmd, vars, &built);
	}
	if (built)
		cmd_path = NULL;
	exit(no_leaks(pids, cmd_path, vars, built));
}

int	execute_builtin_parent(t_parser *parser, t_vars *vars, int *built)
{
	if (!parser || !parser->cmd)
	{
		vars->exit_code = 0;
		return (0);
	}
	if (!parser->next)
		vars->exit_code = builtin(parser, built, vars, 0);
	return (1);
}

int	execute(t_parser *parser, t_pipe_info *pipe_info, t_vars *vars)
{
	int	*pids;
	int	i;
	int	built;

	built = 0;
	if (!execute_builtin_parent(parser, vars, &built))
		return (1);
	if (!init_pid(pipe_info->num_of_process, &pids))
		error_malloc(vars);
	i = -1;
	signal(SIGINT, SIG_IGN);
	while (!built && i++ < pipe_info->num_of_process && parser)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			no_leaks(pids, NULL, vars, built);
		if (pids[i] == 0)
			exec_cmd(parser, pids, i, vars);
		parser = parser->next;
	}
	close_pipes(pipe_info);
	close_std(parser);
	return_value_child(pids, vars);
	free(pids);
	return (1);
}
