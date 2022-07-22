/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:44:17 by meudier           #+#    #+#             */
/*   Updated: 2022/07/22 13:20:06 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	write_error(char *cmd)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin("minishell: command not found: ", cmd);
	temp2 = ft_strjoin(temp1, "\n");
	write (2, temp2, 31 + ft_strlen(cmd));
	free(temp2);
	free(temp1);
}

void	write_is_a_directory(char *cmd, t_vars *vars, int *built)
{
	char	*temp1;

	temp1 = ft_strjoin(cmd, ": is a directory\n");
	write (2, temp1, 17 + ft_strlen(cmd));
	free(temp1);
	vars->exit_code = 126;
	*built = 1;
}

void	clear_err_pars(t_lexer *lexer, t_parser *parser, t_pipe_info *pipe_info)
{
	close_std(parser);
	close_pipes(pipe_info);
	lst_clear_parser(parser);
	lst_clear_lexer(lexer);
}

void	error_malloc_pipe_fd(t_lexer *lst_lexer, t_vars *vars, int i,
	int **pipes)
{
	int	y;

	y = 0;
	write(2, "minishell: pipe: too many open files descriptors\n", 49);
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
