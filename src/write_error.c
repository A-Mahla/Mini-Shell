/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:44:17 by meudier           #+#    #+#             */
/*   Updated: 2022/07/19 16:04:27 by amahla           ###   ########.fr       */
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
	lst_clear_parser(parser);
	lst_clear_lexer(lexer);
	close_pipes(pipe_info);
	close_std(parser);
}
