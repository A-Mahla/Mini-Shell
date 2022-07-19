/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 08:34:14 by meudier           #+#    #+#             */
/*   Updated: 2022/07/19 14:11:35 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	dup_fd(t_parser *parser)
{
	t_in	*last_in;

	last_in = parser->stdin;
	if (last_in)
	{
		while (last_in->next)
		{
			if (last_in->stdin < 0)
				return (0);
			last_in = last_in->next;
		}
		if (last_in->stdin < 0)
			return (0);
		if (last_in->stdin != 0)
			dup2(last_in->stdin, STDIN_FILENO);
	}
	if (parser->stdout < 0)
		return (0);
	if (parser->stdout != 1)
		dup2(parser->stdout, STDOUT_FILENO);
	return (1);
}
