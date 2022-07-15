/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceeudier <maxenceeudier@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 10:48:14 by maxenceeudi       #+#    #+#             */
/*   Updated: 2022/07/15 21:43:28 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int is_already_a_var(t_vars *vars, char *str)
{
    t_env   *last_env;
	t_env   *last_var;
    int     i;
    char     last;
    char    *temp;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    last = str[i];
    str[i] = 0;
	last_env = vars->envl;
	last_var = vars->var;
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
    str[i] = last;
    return (0);
}

int is_already_a_env(t_vars *vars, char *str)
{
    t_env   *last;
    int     i;
    char    c;
    char    *temp;
	int		empty_value;

    i = 0;
	empty_value = 0;
    while (str[i] && str[i] != '=')
        i++;
	if (str[i] == '=' && !str[i + 1])
		empty_value = 1;
    c = str[i];
    str[i] = 0;
    last = vars->envl;
    while (last)
    {
        if (ft_strcmp(str, last->key) == 0)
        {
            if (c)
            {
                temp = last->value;
				if (empty_value)
					last->value = cpy("\"\"");
				else
                	last->value = cpy(str + i + 1);
                free (temp);
            }
            return (1);
        }
        last = last->next;
    }
    str[i] = c;
    return (0);
}

void	push_var_to_env(char *str, t_vars *vars, t_env **begin_var, t_env **begin_env)
{
	t_env	*last;
	t_env	*prev;
	t_env	*temp;

	last = *begin_var;
	prev = NULL;
	while (last)
	{
		if (ft_strcmp(str, last->key) == 0)
		{
			temp = last;
			if (!prev)
				*begin_var = last->next;
			else
				prev->next = prev->next->next;
			temp->next = *begin_env;
			*begin_env = temp;
		}
		prev = last;
		last = last->next;
	}
	if (!is_already_a_env(vars, str))
		push_env(&(vars->envl), str, vars);
}

void	remove_if(char *str, t_env **begin, int (*cmp)(const char *, const char *))
{
	t_env	*prev;
	t_env	*current;
	t_env	*temp;

	current = *begin;
	prev = NULL;
	while (current)
	{
		if (cmp(str, current->key) == 0)
		{
			temp = current;
			if (prev == NULL)
				*begin = current->next;
			else
				prev->next = prev->next->next;
			free(temp->key);
			free(temp->value);
			free(temp);
		}
		prev = current;
		current = current->next;
	}
}

void	remove_if_2(t_env **begin)
{
	t_env	*prev;
	t_env	*current;
	t_env	*temp;

	current = *begin;
	prev = NULL;
	while (current)
	{
		if (!*(current->value))
		{
			temp = current;
			if (prev == NULL)
				*begin = current->next;
			else
				prev->next = prev->next->next;
			free(temp->key);
			free(temp->value);
			free(temp);
		}
		prev = current;
		current = current->next;
	}
}
