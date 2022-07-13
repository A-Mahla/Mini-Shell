/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:13:47 by meudier           #+#    #+#             */
/*   Updated: 2022/07/14 00:51:48 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int env(t_parser *parser, int *built, t_env *envl)
{
	t_env   *last;
	int     out;

	*built = 1;
	out = parser->stdout;
	last = envl;
	while (last)
	{
		if (*(last->value))
		{
			write(out, last->key, ft_strlen(last->key));
			write(out, "=", 1);
			write(out, last->value, ft_strlen(last->value));
			write(out, "\n", 1);
		}
		 last = last->next;
	}
	return (0);
}
