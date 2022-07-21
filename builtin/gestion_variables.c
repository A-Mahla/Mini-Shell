/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 10:48:14 by maxenceeudi       #+#    #+#             */
/*   Updated: 2022/07/21 12:24:23 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	push_var_to_env(char *str, t_vars *vars, t_env **begin_var,
t_env **begin_env)
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

void	free_temp(t_env *temp)
{
	free(temp->key);
	free(temp->value);
	free(temp);
}

void	remove_if(char *str, t_env **begin,
int (*cmp)(const char *, const char *))
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
			current = current->next;
			if (prev == NULL)
				*begin = current;
			else
				prev->next = current;
			free_temp(temp);
		}
		else
		{
			prev = current;
			current = current->next;
		}
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
			current = current->next;
			if (prev == NULL)
				*begin = current;
			else
				prev->next = current;
			free_temp(temp);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
