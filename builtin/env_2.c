/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:13:47 by meudier           #+#    #+#             */
/*   Updated: 2022/07/15 21:25:09 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"


void	get_key_value_2(char *str, int is_equal, char **value, t_vars *vars)
{
	int	len;

	len = 0;
	if (is_equal == 1)
	{
		free(*value);
		*value = (char *)malloc(sizeof(char) * 3);
		if (!*value)
			error_malloc(vars);
		ft_memcpy(*value, "\"\"", 2);
		(*value)[2] = '\0';
		return ;
	}
	while (*(str + len))
	{
		(*value)[len] = str[len];
		len++;
	}
	(*value)[len] = 0;
}

void	get_key_value(char *str, char **key, char **value, t_vars *vars)
{
	int		i;
	int		len;
	int		is_equal;

	len = 0;
	is_equal = 0;
	while (str[len] && str[len] != '=')
		len++;
	if (str[len] == '=' && !str[len + 1])
		is_equal = 1;
	*key = (char *)malloc(sizeof(char) * (len + 1));
	if (!*key)
		error_malloc(vars);
	i = 0;
	while (i < len)
	{
		(*key)[i] = str[i];
		i++;
	}
	(*key)[i++] = 0;
	len = ft_strlen(str) - i;
	*value = (char *)malloc(sizeof(char) * (len + 1));
	if (!*value)
		error_malloc(vars);
	get_key_value_2(str + i, is_equal, value, vars);
}

void	push_env(t_env **lst, char *str, t_vars *vars)
{
	t_env	*new;
	t_env	*last;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		error_malloc(vars);
	get_key_value(str, &(new->key), &(new->value), vars);
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

t_env	*get_env(char **env, t_vars *vars)
{
	int		i;
	t_env	*lst;

	lst = NULL;
	i = 0;
	while (env && env[i])
		push_env(&lst, env[i++], vars);
	return (lst);
}

void	lst_clear_envl(t_env *envl)
{
	t_env *temp;

	while (envl)
	{
		temp = envl;
		envl = envl->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}
