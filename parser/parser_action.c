/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:47:27 by meudier           #+#    #+#             */
/*   Updated: 2022/07/21 07:22:09 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	redir_in(t_parser **new, t_lexer **lexer, t_vars *vars)
{
	t_in	*last_in;

	push_in(&((*new)->stdin), open((*lexer)->next->data, O_RDWR | O_APPEND),
		vars);
	last_in = (*new)->stdin;
	while (last_in->next)
		last_in = last_in->next;
	if (last_in->stdin < 0)
	{
		perror((*lexer)->next->data);
		return (0);
	}
	(*lexer) = (*lexer)->next->next;
	return (1);
}

void	wrd(t_parser **new, t_lexer *lexer, t_pipe_info *pipe_info,
	t_vars *vars)
{
	int	i;

	if (pipe_info->in)
		push_in_front(&((*new)->stdin), pipe_info->in, vars);
	if (pipe_info->out && (*new)->stdout == 1)
		(*new)->stdout = pipe_info->out;
	(*new)->cmd = cpy(lexer->data);
	(*new)->arg = ft_calloc(sizeof(char *), (get_num_of_arg(lexer) + 1));
	if (!(*new)->arg)
		error_malloc_parser(vars);
	i = 0;
	while (lexer && lexer->type != PIPE)
	{
		while (lexer && lexer->type == WRD)
		{
			lexer->type = EMPTY;
			(*new)->arg[i++] = get_arg(lexer->data, vars);
			lexer = lexer->next;
		}
		if (lexer && lexer->type != WRD && lexer->type != PIPE)
		{
			if (lexer->type == EMPTY)
				lexer = lexer->next;
			else if (lexer && lexer->next)
				lexer = lexer->next->next;
			else if (lexer)
				lexer = lexer->next;
		}
	}
	(*new)->arg[i] = NULL;
}
				
			

int	redir_out(t_parser **new, t_lexer **lexer, t_pipe_info *pipe_info,
	t_vars *vars)
{
	int	temp;

	temp = 0;
	if ((*lexer)->next->type == WRD)
	{
		temp = (*new)->stdout;
		(*new)->stdout = open((*lexer)->next->data, \
		O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if ((*new)->stdout < 0)
		{
			perror((*lexer)->next->data);
			close (temp);
			return (0);
		}
		if (temp != 1 && is_not_a_pipe(temp, \
		pipe_info->pipes, pipe_info->num_of_process))
			close(temp);
		(*lexer) = (*lexer)->next->next;
	}
	else
		error_parser(vars);
	return (1);
}

int	redir_out_append(t_parser **new, t_lexer **lexer, \
t_pipe_info *pipe_info, t_vars *vars)
{
	int	temp;

	temp = 0;
	if ((*lexer)->next->type == WRD)
	{	
		temp = (*new)->stdout;
		(*new)->stdout = open((*lexer)->next->data, \
		O_WRONLY | O_APPEND | O_CREAT, 0777);
		if ((*new)->stdout < 0)
		{
			perror((*lexer)->next->data);
			return (0);
		}
		if (temp != 1 && is_not_a_pipe(temp, \
		pipe_info->pipes, pipe_info->num_of_process))
			close(temp);
		(*lexer) = (*lexer)->next->next;
	}
	else
		error_parser(vars);
	return (1);
}
