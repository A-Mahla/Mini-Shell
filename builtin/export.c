/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ammah <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 12:47:39 by ammah             #+#    #+#             */
/*   Updated: 2022/07/12 12:54:34 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void   sort_lst(t_env **begin)
{
    t_env   *current;
    t_env   *prev;
    t_env   *temp;

    current = *begin;
    prev = NULL;
    while (current->next)
    {
            if (ft_strcmp(current->key, current->next->key) > 0)
            {
                if (prev == NULL)
                {
                    temp = current;
                    *begin = temp->next;
                    current->next = temp->next->next;
                    (*begin)->next = current;
                }
                else
                {
                    temp = current;
                    prev->next = current->next;
                    current->next = prev->next->next;
                    prev->next->next = current;
                }
                current = *begin;
                prev = NULL;
            }
            else
            {
                prev = current;
                current = current->next;
            }
    }
}

t_env *cpy_lst(t_env *envl)
{
    t_env   *cpy_lst;
    t_env   *last;
    char    *temp;

    cpy_lst = NULL;
    last = envl;
    while (last)
    {
        temp = ft_strjoin_eq(last->key, last->value);
        push_env(&cpy_lst, temp);
        free (temp);
        last = last->next;
    }
    return (cpy_lst);
}

void    print_sort_env(t_parser *parser, t_env *envl)
{
    t_env   *sort_env;
    int     out;

    out = parser->stdout;
    sort_env = cpy_lst(envl);
    //sort_env = envl;
    sort_lst(&sort_env);
    while(sort_env)
    {
		write(out, "declare -x ", 11);
        write(out, sort_env->key, ft_strlen(sort_env->key));
        if (*(sort_env->value))
        {
            write(out, "=", 1);
            write(out, sort_env->value, ft_strlen(sort_env->value));
        }
        write(out, "\n", 1);
        sort_env = sort_env->next;
    }
    lst_clear_envl(sort_env);
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
