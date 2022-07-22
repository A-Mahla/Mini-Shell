/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:13:47 by meudier           #+#    #+#             */
/*   Updated: 2022/07/21 11:30:18 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	env(t_parser *parser, int *built, t_env *envl)
{
	int		out;

	*built = 1;
	out = parser->stdout;
	if (parser->arg[1])
	{
		write (out, "env: ", 5);
		write (out, parser->arg[1], ft_strlen(parser->arg[1]));
		write (out, ": No such file or directory\n", 28);
		return (127);
	}
	while (envl)
	{
		if (*(envl->value))
		{
			write(out, envl->key, ft_strlen(envl->key));
			write(out, "=", 1);
			if (ft_strcmp(envl->value, "\"\"") != 0)
				write(out, envl->value, ft_strlen(envl->value));
			write(out, "\n", 1);
		}
		envl = envl->next;
	}
	return (0);
}
