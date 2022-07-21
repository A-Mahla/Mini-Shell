/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:26 by maxenceeudi       #+#    #+#             */
/*   Updated: 2022/07/21 14:18:31 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	create_new_2(t_parser **new, t_lexer **lexer, t_parser *parser,
t_vars *vars)
{
	int	error_code;

	error_code = 1;
	if ((*lexer)->type == REDIR_IN && (*lexer)->next
		&& (*lexer)->next->type == WRD)
		error_code = redir_in(new, lexer, vars);
	else if ((*lexer)->type == WRD)
		wrd(new, *lexer, vars->pipe_info, vars);
	else if ((*lexer)->type == REDIR_OUT && (*lexer)->next
		&& (*lexer)->next->type == WRD)
		error_code = redir_out(new, lexer, vars->pipe_info, vars);
	else if ((*lexer)->type == REDIR_OUT_APPEND
		&& (*lexer)->next && (*lexer)->next->type == WRD)
		error_code = redir_out_append(new, lexer, vars->pipe_info, vars);
	else if ((*lexer)->type == HERDOC && (*lexer)->next
		&& (*lexer)->next->type == WRD)
		error_code = heredoc(new, lexer, vars, parser);
	else if ((*lexer)->type == EMPTY)
		(*lexer) = (*lexer)->next;
	else
	{
		write (2, "minishell: syntax error\n", 24);
		return (0);
	}
	return (error_code);
}

int	create_new(t_parser **new, t_lexer **lexer, t_parser *parser,
t_vars *vars)
{
	int	error_code;

	error_code = 1;
	while ((*lexer) && (*lexer)->type != PIPE)
	{
		error_code = create_new_2(new, lexer, parser, vars);
		if (!error_code)
			return (0);
	}
	return (1);
}

int	push_parser(t_parser **parser, t_lexer **lexer, \
t_pipe_info *pipe_info, t_vars *vars)
{
	t_parser	*new;
	t_parser	*last;

	(void)pipe_info;
	new = (t_parser *)ft_calloc(sizeof(t_parser), 1);
	if (!new)
		error_malloc_parser(vars);
	init_parser(new);
	if (!create_new(&new, lexer, *parser, vars))
	{
		close_std(new);
		lst_clear_parser(new);
		return (0);
	}
	if (!*parser)
		*parser = new;
	else
	{
		last = *parser;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (1);
}

void	init_pipe_info_in_n_out(t_pipe_info *pipe_info, int j)
{
	if (pipe_info->pipes && j != 0)
		pipe_info->in = pipe_info->pipes[j][0];
	else
		pipe_info->in = 0;
	if (pipe_info->pipes && j != pipe_info->num_of_process -1)
		pipe_info->out = pipe_info->pipes[j + 1][1];
	else
		pipe_info->out = 0;
}

int	parser(t_parser **parser, t_lexer *lexer, t_pipe_info *pipe_info,
t_vars *vars)
{
	int			j;

	*parser = NULL;
	j = 0;
	while (lexer)
	{
		if (lexer->type != PIPE)
		{
			init_pipe_info_in_n_out(pipe_info, j);
			j++;
			if (!push_parser(parser, &lexer, pipe_info, vars))
				return (0);
		}
		else if (!j || (lexer->type == PIPE && !lexer->next)
			|| (lexer->type == PIPE && lexer->next->type == PIPE))
		{
			write(2, "minishell: syntax error\n", 24);
			vars->exit_code = 2;
			return (0);
		}
		else
			lexer = lexer->next;
	}
	return (1);
}
