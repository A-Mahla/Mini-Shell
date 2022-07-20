/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:41:17 by maxenceeudi       #+#    #+#             */
/*   Updated: 2022/07/20 18:44:21 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

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

int	init_pid(int num_of_process, int **pids)
{
	*pids = (int *)ft_calloc(sizeof(int), num_of_process + 1);
	if (!*pids)
		return (0);
	return (1);
}

void	exec_cmd(t_parser *parser, int *pids, int i, t_vars *vars)
{
	char	*cmd_path;
	int		built;
	char	**new_env;

	built = 0;
	if (!parser->cmd)/* || strcmp(parser->cmd, "!") == 0
		|| strcmp(parser->cmd, ":") == 0)*/
	{
		vars->exit_code = 0;
		exit(no_leaks(pids, NULL, vars, built));
	}
	vars->exit_code = builtin(parser, &built, vars, 1);
	sig_init();
	signal(SIGQUIT, SIG_DFL);
	if (!built && !get_cmdpath(parser, &cmd_path, i, vars->envl))
	{
		vars->exit_code = 127;
		exit(no_leaks(pids, cmd_path, vars, 1));
	}
	if (!built && !dup_fd(parser))
	{
		cmd_path = NULL;
		exit(no_leaks(pids, cmd_path, vars, 0));
	}
	close_pipes(vars->pipe_info);
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

/*void	fork_n_execute(int i, int *pids, t_vars *vars, int built)
{
	
}*/

int	execute(t_parser *parser, t_pipe_info *pipe_info, t_vars *vars)
{
	int	*pids;
	int	i;
	int	built;

	built = 0;
	if (!parser->cmd || strcmp(parser->cmd, "!") == 0
		|| strcmp(parser->cmd, ":") == 0)
	{
		vars->exit_code = 0;
		close_pipes(pipe_info);
		close_std(parser);
		return (1);
	}
	if (!parser->next)
		vars->exit_code = builtin(parser, &built, vars, 0);
	if (!init_pid(pipe_info->num_of_process, &pids))
		error_malloc(vars);
	i = 0;
	signal(SIGINT, SIG_IGN);
	while (!built && i < pipe_info->num_of_process && parser)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			no_leaks(pids, NULL, vars, built);
		if (pids[i] == 0)
			exec_cmd(parser, pids, i, vars);
		parser = parser->next;
		i++;
	}
	close_pipes(pipe_info);
	close_std(parser);
	return_value_child(pids, vars);
	free(pids);
	return (1);
}
