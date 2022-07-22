/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:37:59 by meudier           #+#    #+#             */
/*   Updated: 2022/07/21 11:19:55 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	cd(t_parser *parser, int *built, t_env *envl)
{
	t_env	*last;
	char	*old;

	*built = 1;
	if (!parser->arg[1])
		return (1);
	if (parser->arg[2] || chdir(parser->arg[1]) <= -1)
	{
		if (parser->arg[2])
			write (parser->stdout, "minishell: cd: too many arguments\n", 34);
		else
			perror(parser->arg[1]);
		return (1);
	}
	last = envl;
	while (last && ft_strcmp(last->key, "PWD") != 0)
		last = last->next;
	old = last->value;
	last->value = getcwd(NULL, 0);
	last = envl;
	while (last && ft_strcmp(last->key, "OLDPWD") != 0)
		last = last->next;
	free(last->value);
	last->value = old;
	return (0);
}
