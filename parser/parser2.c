/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:52:13 by meudier           #+#    #+#             */
/*   Updated: 2022/07/17 15:34:02 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	push_in(t_in **stdin, int data, t_vars *vars)
{
	t_in	*new;
	t_in	*last;

	new = (t_in *)ft_calloc(sizeof(t_in), 1);
	if (!new)
		error_malloc_parser(vars);
	new->stdin = data;
	new->next = NULL;
	if (!*stdin)
		*stdin = new;
	else
	{
		last = *stdin;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	push_in_front(t_in **stdin, int data, t_vars *vars)
{
	t_in	*new;

	new = (t_in *)ft_calloc(sizeof(t_in), 1);
	if (!new)
		error_malloc_parser(vars);
	new->stdin = data;
	new->next = NULL;
	if (!*stdin)
		*stdin = new;
	else
	{
		new->next = *stdin;
		*stdin = new;
	}
}

char	*get_arg(char *str, t_vars *vars)
{
	int		i;
	int		len;
	char	*arg;

	i = 0;
	len = ft_strlen(str);
	arg = (char *)ft_calloc(sizeof(char), len + 1);
	if (!arg)
		error_malloc_parser(vars);
	while (str[i])
	{
		arg[i] = str[i];
		i++;
	}
	arg[i] = 0;
	return (arg);
}

void	lst_clear_parser(t_parser *parser)
{
	t_parser	*temp;
	t_in		*temp_in;

	while (parser)
	{
		temp = parser;
		parser = parser->next;
		free(temp->cmd);
		clear_tab(temp->arg);
		while (temp->stdin)
		{
			temp_in = temp->stdin;
			temp->stdin = temp->stdin->next;
			temp_in->stdin = 0;
			free(temp_in);
		}
		temp->stdout = 0;
		free(temp);
	}
}
