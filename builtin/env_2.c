/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:13:47 by meudier           #+#    #+#             */
/*   Updated: 2022/07/15 13:49:33 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	get_key_value(char *str, char **key, char **value, t_vars *vars)
{
	int		i;
	int		len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	*key = (char *)malloc(sizeof(char) * (len + 1));
	if (!*key)
		error_malloc(vars);
	i = 0;
	while (i < len)
	{
		(*key)[i] = str[i];
		i++;
	}
	(*key)[i] = 0;
	i++;
	len = ft_strlen(str) - i;
	*value = (char *)malloc(sizeof(char) * (len + 1));
	if (!*value)
		error_malloc(vars);
	len = 0;
	while (i < ft_strlen(str))
		(*value)[len++] = str[i++];
	(*value)[len] = 0;
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
