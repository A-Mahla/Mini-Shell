/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_variables2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:23:01 by meudier           #+#    #+#             */
/*   Updated: 2022/07/21 14:07:16 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	search_in(t_env *var, char *str, int i)
{
	t_env	*last_var;
	char	*temp;

	last_var = var;
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
	return (0);
}

int	is_already_a_var(t_vars *vars, char *str)
{
	int		i;
	char	last;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	last = str[i];
	str[i] = 0;
	if (search_in(vars->var, str, i))
		return (1);
	if (search_in(vars->envl, str, i))
		return (1);
	str[i] = last;
	return (0);
}

void	is_already_a_env2(char *str, char *c, int *empty_value, int *i)
{
	*i = 0;
	*empty_value = 0;
	while (str[*i] && str[*i] != '=')
		(*i)++;
	if (str[*i] == '=' && !str[*i + 1])
		*empty_value = 1;
	*c = str[*i];
	str[*i] = 0;
}

int	is_already_a_env(t_vars *vars, char *str)
{
	t_env	*last;
	int		i;
	char	c;
	int		empty_value;

	is_already_a_env2(str, &c, &empty_value, &i);
	last = vars->envl;
	while (last)
	{
		if (ft_strcmp(str, last->key) == 0 && c)
		{
			if (empty_value)
				last->value = cpy("\"\"");
			else
				last->value = cpy(str + i + 1);
			return (1);
		}
		else if (ft_strcmp(str, last->key) == 0)
			return (1);
		last = last->next;
	}
	str[i] = c;
	return (0);
}
