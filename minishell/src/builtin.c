/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:37:59 by meudier           #+#    #+#             */
/*   Updated: 2022/07/07 12:23:04 by meudier          ###   ########.fr       */
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
        write(out, last->key, ft_strlen(last->key));
        write(out, "=", 1);
        write(out, last->value, ft_strlen(last->value));
        write(out, "\n", 1);
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

int is_already_a_var(t_vars *vars, char *str)
{
    t_env   *last_env;
	t_env   *last_var;
    int     i;
    char    *temp;

    i = 0;
    while (str[i] != '=')
        i++;
    str[i] = 0;
	last_env = vars->envl;
	last_var = vars->var;
	while (last_env)
	{
		if (ft_strncmp(str, last_env->key, i) == 0)
        {
            temp = last_env->value;
            last_env->value = cpy(str + i + 1);
            free(temp);
            return (1);
        }
		last_env = last_env->next;
	}
	while (last_var)
	{
		if (ft_strncmp(str, last_var->key, i) == 0)
        {
            temp = last_var->value;
            last_var->value = cpy(str + i + 1);
            free(temp);
            return (1);
        }
		last_var = last_var->next;
	}
    str[i] = '=';
    return (0);
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
    return (1);
}