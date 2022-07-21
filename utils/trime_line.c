/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trime_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 10:56:20 by meudier           #+#    #+#             */
/*   Updated: 2022/07/21 10:56:38 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	trim_line(char *line)
{
	int	i;

	i = 0;
	while (*(line + i))
	{
		while (*(line + i) == '\"' || *(line + i) == '\'')
		{
			i++;
			while (*(line + i)
				&& !(*(line + i) == '\"' || *(line + i) == '\''))
				i++;
			if (*(line + i))
				i++;
			else
				return ;
		}
		if (*(line + i) == '\t')
			*(line + i) = ' ';
		i++;
	}
}
