/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:02:07 by meudier           #+#    #+#             */
/*   Updated: 2022/06/27 09:47:09 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;

	if (!s1)
		return (NULL);
	dup = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}
