/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceeudier <maxenceeudier@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:37:59 by meudier           #+#    #+#             */
/*   Updated: 2022/07/08 10:54:53 by maxenceeudi      ###   ########.fr       */
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

int pwd(t_parser *parser, int *built)
{
    char    *temp;

    *built = 1;
    temp = getcwd(NULL, 0);
    write (parser->stdout, temp, ft_strlen(temp));
    write (parser->stdout, "\n", 1);
    free(temp);
    return (1);
}

int env(t_parser *parser, int *built, t_env *envl)
{
    t_env   *last;
    int     out;

    *built = 1;
    out = parser->stdout;
    last = envl;
    while(last)
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
    return (1);
}

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

void    print_sort_env(t_parser *parser, t_env *envl)
{
    t_env   *last;
    int     out;

    out = parser->stdout;
    last = envl;
    while(last)
    {
        write(out, last->key, ft_strlen(last->key));
        if (*(last->value))
        {
            write(out, "=", 1);
            write(out, last->value, ft_strlen(last->value));
        }
        write(out, "\n", 1);
        last = last->next;
    }
}

void    export(t_parser *parser, int *built, t_vars *vars)
{
    int i;

    *built = 1;
    i = 1;
    if (!parser->arg[1])
        print_sort_env(parser, vars->envl);
    else
    {
        while (parser->arg[i])
        {
            push_var_to_env(parser->arg[i], vars, &(vars->var), &(vars->envl));
            i++;
        }
    }
}

void    unset(t_parser *parser, int *built, t_vars *vars)
{
    int i;

    *built = 1;
    if (!parser->arg[1])
        return ;
    i = 1;
    while (parser->arg[i])
    {
        remove_if(parser->arg[i], &(vars->envl), &ft_strcmp);
        remove_if(parser->arg[i], &(vars->var), &ft_strcmp);
        i++;
    }
}

int	builtin(t_parser *parser, int *built, t_vars *vars)
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
    return (1);
}