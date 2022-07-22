/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lexer_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:39:16 by meudier           #+#    #+#             */
/*   Updated: 2022/07/22 17:24:05 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ft_get_quote(int *len, const char *s)
{
	if (*(s + *len) == '\'')
	{
		(*len)++;
		while (*(s + *len) && *(s + *len) != '\'')
			(*len)++;
		if (*(s + *len) && *(s + *len) == '\'')
			(*len)++;
	}
	else if (*(s + *len) == '\"')
	{
		(*len)++;
		while (*(s + *len) && *(s + *len) != '\"')
			(*len)++;
		if (*(s + *len) && *(s + *len) == '\"')
			(*len)++;
	}
}

int	ft_get_size_2(int j, int *i, const char *s, char *meta)
{
	if (j < 3 && s[*i] == meta[j] && s[*i])
	{
		while (s[*i] == meta[j] && s[*i])
			(*i)++;
		return (0);
	}
	else if (*(s + *i) && *(s + *i) != ' ' && !is_meta(*(s + *i), meta))
	{	
		while (*(s + *i) && *(s + *i) != ' ' && !is_meta(*(s + *i), meta))
		{
			if (*(s + *i) == '\'' || *(s + *i) == '\"')
				ft_get_quote(i, s);
			else
				(*i)++;
		}
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

	meta = "><|";
	i = 0;
	count = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] == ' ' && s[i])
			i++;
		while (meta[j] && s[i])
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
	else if (*s && *s != ' ' && !is_meta(*s, meta))
	{	
		while (*(s + *len) && *(s + *len) != ' ' && !is_meta(*(s + *len), meta))
		{
			if (*(s + *len) == '\'' || *(s + *len) == '\"')
				ft_get_quote(len, s);
			else
				(*len)++;
		}
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
	meta = "><|";
	while (s[*index] == ' ' && s[*index])
		(*index)++;
	while (meta[j])
		if (!ft_get_word_2(j++, &len, s + *index, meta))
			break ;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	if (j > 4)
		(*index)++;
	while (i < len)
		word[i++] = s[(*index)++];
	word[i] = 0;
	return (word);
}
