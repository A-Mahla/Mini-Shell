/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:23:13 by ammah             #+#    #+#             */
/*   Updated: 2022/07/19 14:13:11 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	error_malloc(t_vars *vars)
{
	if (!vars)
		exit(EXIT_FAILURE);
	write(2, "minishell: malloc failed\n", 25);
	if (vars->pipe_info->pipes)
		close_pipes(vars->pipe_info);
	close_std(vars->lst_parser);
	lst_clear_lexer(vars->lst_lexer);
	lst_clear_parser(vars->lst_parser);
	lst_clear_envl(vars->envl);
	lst_clear_envl(vars->var);
	clear_history();
	exit(EXIT_FAILURE);
}

void	error_malloc_lexer(t_lexer *lst_lexer, t_vars *vars)
{
	write(2, "minishell: malloc failed\n", 25);
	if (lst_lexer)
		lst_clear_lexer(lst_lexer);
	lst_clear_envl(vars->envl);
	lst_clear_envl(vars->var);
	clear_history();
	exit(EXIT_FAILURE);
}

void	error_malloc_pipe(t_lexer *lst_lexer, t_vars *vars, int i, int **pipes)
{
	int	y;

	y = 0;
	write(2, "minishell: malloc failed\n", 25);
	while (y < i)
		free(pipes[y++]);
	if (pipes)
		free(pipes);
	lst_clear_lexer(lst_lexer);
	lst_clear_envl(vars->envl);
	lst_clear_envl(vars->var);
	clear_history();
	exit(EXIT_FAILURE);
}

void	error_malloc_parser(t_vars *vars)
{
	write(2, "minishell: malloc failed\n", 25);
	if (vars->pipe_info->pipes)
		close_pipes(vars->pipe_info);
	close_std(vars->lst_parser);
	lst_clear_lexer(vars->lst_lexer);
	lst_clear_parser(vars->lst_parser);
	lst_clear_envl(vars->envl);
	lst_clear_envl(vars->var);
	clear_history();
	exit(EXIT_FAILURE);
}

void	error_parser(t_vars *vars)
{
	if (vars->pipe_info->pipes)
		close_pipes(vars->pipe_info);
	close_std(vars->lst_parser);
	lst_clear_lexer(vars->lst_lexer);
	lst_clear_parser(vars->lst_parser);
	lst_clear_envl(vars->envl);
	lst_clear_envl(vars->var);
	clear_history();
	exit(EXIT_FAILURE);
}
