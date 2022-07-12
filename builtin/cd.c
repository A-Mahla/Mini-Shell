/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:37:59 by meudier           #+#    #+#             */
/*   Updated: 2022/07/12 12:32:55 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int    cd(t_parser *parser, int *built, t_env *envl)
{
    t_env	*last;
	char	*old;
	DIR	    *dir;

    *built  = 1;
    dir = opendir(parser->arg[1]);
    if (!dir || parser->arg[2])
    {
        if (parser->arg[2])
            write(2, "Error: cd: too many files\n", 27);
        else
            perror(parser->arg[1]);
        return (0);
    }
    if (chdir(parser->arg[1]) <= -1)
        perror(parser->arg[1]);
    closedir(dir);
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
    return (1);
}
