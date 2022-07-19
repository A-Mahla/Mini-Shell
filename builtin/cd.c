/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:37:59 by meudier           #+#    #+#             */
/*   Updated: 2022/07/19 12:49:33 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int    cd(t_parser *parser, int *built, t_env *envl)
{
    t_env	*last;
	char	*old;

    *built  = 1;
	if (!parser->arg[1])
		return (1);
	if (parser->arg[2])
	{
		write (parser->stdout, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	if (chdir(parser->arg[1]) <= -1)
	{
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
