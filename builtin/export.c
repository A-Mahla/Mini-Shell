/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ammah <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 12:47:39 by ammah             #+#    #+#             */
/*   Updated: 2022/07/15 21:22:18 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	swap_list(t_env *current, t_env *next)
{
	t_env	*swap;

	swap = next->next;
	next->next = current;
	current->next = swap;
}

void   sort_lst(t_env **begin)
{
	t_env   *current;
	t_env   *prev;
	t_env   *next;

	current = *begin;
	prev = NULL;
	while (current->next)
	{
		next = current->next;
		if (ft_strcmp(current->key, next->key) > 0)
		{
			swap_list(current, next);
			if (!prev)
				*begin = next;
			else
				prev->next = next;
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

t_env *cpy_lst(t_env *envl, t_vars *vars)
{
    t_env   *cpy_lst;
    t_env   *last;
    char    *temp;

    cpy_lst = NULL;
    last = envl;
    while (last)
    {
		if (*(last->value))
        	temp = ft_strjoin_eq(last->key, last->value);
		else
			temp = cpy(last->key);
        push_env(&cpy_lst, temp, vars);
        free (temp);
        last = last->next;
    }
    return (cpy_lst);
}

void    print_sort_env(t_parser *parser, t_env *envl, t_vars *vars)
{
    t_env   *sort_env;
    int     out;

    out = parser->stdout;
    sort_env = cpy_lst(envl, vars);
    sort_lst(&sort_env);
    while (sort_env)
    {
		write(out, "declare -x ", 11);
        write(out, sort_env->key, ft_strlen(sort_env->key));
        if (*(sort_env->value))
        {
            write(out, "=", 1);
			if (ft_strcmp(sort_env->value, "\"\"") != 0)
				write(out, "\"", 1);
            write(out, sort_env->value, ft_strlen(sort_env->value));
        }
		if (*(sort_env->value) && ft_strcmp(sort_env->value, "\"\"") != 0)
			write(out, "\"", 1);
        write(out, "\n", 1);
        sort_env = sort_env->next;
    }
    lst_clear_envl(sort_env);
}

int	export(t_parser *parser, int *built, t_vars *vars)
{
    int i;

    *built = 1;
    i = 1;
    if (!parser->arg[1])
        print_sort_env(parser, vars->envl, vars);
    else
    {
        while (parser->arg[i])
        {
			if (!check_export(parser->arg[i]))
			{
				write(2, "minishell: export: '", 20);
				write(2, parser->arg[i], ft_strlen(parser->arg[i]));
				write(2, "': not a valid identifier\n", 26);
				return (1);
			}
            push_var_to_env(parser->arg[i], vars, &(vars->var), &(vars->envl));
            i++;
        }
    }
	return (0);
}
