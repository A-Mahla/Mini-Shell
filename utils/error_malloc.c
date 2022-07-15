/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ammah <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:23:13 by ammah             #+#    #+#             */
/*   Updated: 2022/07/15 14:27:17 by ammah            ###   ########.fr       */
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
	clear_history();
	exit(EXIT_FAILURE);
}
