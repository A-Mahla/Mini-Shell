/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:39:31 by ammah             #+#    #+#             */
/*   Updated: 2022/07/19 15:34:12 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	check_is_option(char *arg, int *option)
{
	int	i;

	i = 0;
	if (*(arg + i) == '-')
	{
		i++;
		while (*(arg + i))
		{
			if (*(arg + i) != 'n')
				break ;
			if (*(arg + i + 1) == '\0')
			{
				*option = 1;
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	is_option(char **arg, int *y)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	while (arg[i] && check_is_option(arg[i], &option))
	{
		(*y)++;
		i++;
	}
	return (option);
}

int	echo(t_parser *parser, int *built)
{
	int	y;
	int	out;
	int	option;

	*built = 1;
	y = 1;
	option = is_option(parser->arg, &y);
	out = parser->stdout;
	while (parser->arg[y])
	{
		write(out, parser->arg[y], ft_strlen(parser->arg[y]));
		if (parser->arg[y + 1])
			write(out, " ", 1);
		y++;
	}
	if (!option)
		write(out, "\n", 1);
	return (0);
}
