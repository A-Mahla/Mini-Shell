/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:05:26 by maxenceeudi       #+#    #+#             */
/*   Updated: 2022/07/13 18:36:16 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	init_parser(t_parser *new)
{
	new->cmd = NULL;
	new->stdin = NULL;
	new->stdout = 1;
	new->next = NULL;
	new->prev = NULL;
}

void	create_new(t_parser **new, t_lexer **lexer, t_pipe_info *pipe_info)
{
	while ((*lexer) && (*lexer)->type != PIPE)
	{
		if ((*lexer)->type == REDIR_IN && (*lexer)->next)
			redir_in(new, lexer);
		else if ((*lexer)->type == WRD)
			wrd(new, lexer, pipe_info);
		else if ((*lexer)->type == REDIR_OUT && (*lexer)->next)
			redir_out(new, lexer, pipe_info);
		else if ((*lexer)->type == REDIR_OUT_APPEND && (*lexer)->next)
			redir_out_append(new, lexer, pipe_info);
		else if ((*lexer)->type == HERDOC && (*lexer)->next)
			heredoc(new, lexer);
		else if ((*lexer)->type == EMPTY)
			(*lexer) = (*lexer)->next;
	}
}

void	push_parser(t_parser **parser, t_lexer **lexer, \
t_pipe_info *pipe_info)
{
	t_parser	*new;
	t_parser	*last;

	new = (t_parser *)ft_calloc(sizeof(t_parser), 1);
	if (!new)
		exit (1);
	init_parser(new);
	create_new(&new, lexer, pipe_info);
	if (!*parser)
	{
		new->prev = NULL;
		*parser = new;
	}	
	else
	{
		last = *parser;
		while (last->next)
			last = last->next;
		last->next = new;
		new->prev = last;
	}
}

t_parser	*parser(t_lexer *lexer, t_pipe_info *pipe_info)
{
	t_parser	*parser;
	int			j;

	parser = NULL;
	j = 0;
	while (lexer)
	{
		if (lexer->type != PIPE)
		{
			if (pipe_info->pipes && j != 0)
				pipe_info->in = pipe_info->pipes[j][0];
			else
				pipe_info->in = 0;
			if (pipe_info->pipes && j != pipe_info->num_of_process -1)
				pipe_info->out = pipe_info->pipes[j + 1][1];
			else
				pipe_info->out = 0;
			j++;
			push_parser(&parser, &lexer, pipe_info);
		}	
		else
			lexer = lexer->next;
	}
	return (parser);
}
