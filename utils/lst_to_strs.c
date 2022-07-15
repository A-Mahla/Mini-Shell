/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_strs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ammah <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 19:44:25 by ammah             #+#    #+#             */
/*   Updated: 2022/07/15 21:42:32 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	size_str(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size = size + ft_strlen(env->key) + ft_strlen(env->value) + 2;
		env = env->next;
	}
	return (size);
}

void	cpy_lst_to_str(char *str, t_env *env)
{
	int	i;
	
	i = 0;
	while (env)
	{
		ft_memcpy(str + i, env->key, ft_strlen(env->key));
		i += ft_strlen(env->key);
		if (*(env->value))
		{
			*(str + i++) = '=';
			ft_memcpy(str + i, env->value, ft_strlen(env->value));
		}
		i += ft_strlen(env->value);
		if (env->next)
			*(str + i++) = '\n';
		env = env->next;
	}
	*(str + i) = '\0';
}

char	**lst_to_strs(t_env *env)
{
	char	*temp;
	char	**strs;

	remove_if_2(&env);
	temp = malloc(size_str(env) * sizeof(char));
	if (!temp)
		return (NULL);
	cpy_lst_to_str(temp, env);
	strs = ft_split(temp, '\n');
	free(temp);
	return (strs);
}
