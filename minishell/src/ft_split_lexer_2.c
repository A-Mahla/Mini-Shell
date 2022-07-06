/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lexer_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceeudier <maxenceeudier@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:39:16 by meudier           #+#    #+#             */
/*   Updated: 2022/07/04 17:43:56 by maxenceeudi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	is_meta(char c, char *meta)
{
	int	i;

	i = 0;
	while (meta[i])
	{
		if (meta[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_get_size_2(int j, int *i, const char *s, char *meta)
{
	if (j < 3 && s[*i] == meta[j] && s[*i])
	{
		while (s[*i] == meta[j] && s[*i])
			(*i)++;
		return (0);
	}
	else if (s[*i] == meta[j] && s[*i])
	{
		(*i)++;
		while (s[*i] != meta[j] && s[*i])
			(*i)++;
		return (0);
	}
	else if (s[*i] != ' ' && !is_meta(s[*i], meta))
	{
		while (s[*i] != ' ' && !is_meta(s[*i], meta) && s[*i])
			(*i)++;
		return (0);
	}
	return (1);
}

int	ft_get_size_1(char const *s)
{
	int		i;
	int		j;
	int		count;
	char	*meta;

	meta = "><|\'\"";
	i = 0;
	count = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] == ' ' && s[i])
			i++;
		while (meta[j])
		{
			if (!ft_get_size_2(j, &i, s, meta))
			{
				count++;
				break ;
			}
			j++;
		}
	}
	return (count);
}

int	ft_get_word_2(int j, int *len, char *s, char *meta)
{
	if (j < 3 && *s == meta[j] && *s)
	{
		while (*(s + *len) == meta[j] && *(s + *len))
			(*len)++;
		return (0);
	}
	else if (*s == meta[j] && *s)
	{
		while (*(s + *len + 1) != meta[j] && *(s + *len + 1))
			(*len)++;
		if (*(s + *len + 1) == 0 && *(s + *len) != meta[j])
		{
			printf("Syntax error: quotes are not close\n");
			*len = 0;
		}
		return (0);
	}
	else if (*s != ' ' && !is_meta(*s, meta))
	{
		while (*(s + *len) != ' ' && !is_meta(*(s + *len), meta) && *(s + *len))
			(*len)++;
		return (0);
	}
	return (1);
}

char	*ft_get_word_1(int *index, char *s)
{
	char	*word;
	char	*meta;
	int		len;
	int		i;
	int		j;

	len = 0;
	j = 0;
	meta = "><|\'\"";
	while (s[*index] == ' ' && s[*index])
		(*index)++;
	while (meta[j])
		if (!ft_get_word_2(j++, &len, s + *index, meta))
			break ;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	if (j > 3)
		(*index)++;
	while (i < len)
		word[i++] = s[(*index)++];
	word[i] = 0;
	return (word);
}
