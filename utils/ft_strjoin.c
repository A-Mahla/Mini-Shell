/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:11:27 by meudier           #+#    #+#             */
/*   Updated: 2022/07/08 14:24:58 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;
	int		size;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	size = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	join = (char *)malloc(sizeof(char) * size + 1);
	if (!join)
		return (NULL);
	j = 0;
	while (s1[j])
		join[i++] = s1[j++];
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = 0;
	return (join);
}

char	*ft_strjoin_bs(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;
	int		size;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	size = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	join = (char *)malloc(sizeof(char) * size + 2);
	if (!join)
		return (NULL);
	j = 0;
	while (s1[j])
		join[i++] = s1[j++];
	join[i++] = '/';
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = 0;
	return (join);
}

char	*ft_strjoin_eq(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;
	int		size;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	size = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	join = (char *)malloc(sizeof(char) * size + 2);
	if (!join)
		return (NULL);
	j = 0;
	while (s1[j])
		join[i++] = s1[j++];
	join[i++] = '=';
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = 0;
	return (join);
}
