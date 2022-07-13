/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:37:59 by meudier           #+#    #+#             */
/*   Updated: 2022/07/13 18:17:09 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int is_init_var(char *word, int *built)
{
    int i;

    i = 0;
    while (word[i])
    {
        if (word[i] == '=')
        {
            *built = 1;
            return (1);
        }  
        i++;
    }
    return (0);
}

int	builtin(t_parser *parser, int *built, t_vars *vars, int pipe)
{
	if (ft_strcmp(parser->cmd, "cd") == 0)
    {
        if (!cd(parser, built, vars->envl))
            return (0);
    }
    else if (ft_strcmp(parser->cmd, "pwd") == 0)
        pwd(parser, built);
    else if (ft_strcmp(parser->cmd, "env") == 0)
        env(parser, built, vars->envl);
    else if (is_init_var(parser->cmd, built))
    {
        if (!is_already_a_var(vars, parser->cmd))
            push_env(&(vars->var), parser->cmd);
    }
    else if (ft_strcmp(parser->cmd, "export") == 0)
        export(parser, built, vars);
    else if (ft_strcmp(parser->cmd, "unset") == 0)
        unset(parser, built, vars);
    else if (ft_strcmp(parser->cmd, "echo") == 0)
        echo(parser, built);
	else if (ft_strcmp(parser->cmd, "exit") == 0)
		ft_exit(vars, built, pipe);
    return (1);
}
