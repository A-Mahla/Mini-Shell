/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 07:02:00 by maxenceeudi       #+#    #+#             */
/*   Updated: 2022/07/04 13:01:19 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

char	**clear_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab && (tab)[i])
		free((tab)[i++]);
	free (tab);
	return (NULL);
}

char	**ft_split_lexer(char const *s)
{
	int		i;
	int		j;
	int		size;
	char	**tab;

	if (!s)
		return (NULL);
	size = ft_get_size_1(s);
	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		tab[i] = ft_get_word_1(&j, (char *)s);
		if (!tab[i])
			return (clear_tab(tab));
		i++;
	}
	tab[i] = 0;
	return (tab);
}
