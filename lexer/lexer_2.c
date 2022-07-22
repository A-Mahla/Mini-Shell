/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:02:23 by meudier           #+#    #+#             */
/*   Updated: 2022/07/22 17:14:43 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h" 

int	ft_check_double_quote(int *len, const char *s)
{
	if (*(s + *len) == '\"')
	{
		(*len)++;
		while (*(s + *len) && *(s + *len) != '\"')
			(*len)++;
		if (*(s + *len) && *(s + *len) == '\"')
			(*len)++;
		else
			return (0);
	}
	return (1);
}

int	check_nb_quote(char *s)
{
	int	i;

	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == '\'')
		{
			(i)++;
			while (*(s + i) && *(s + i) != '\'')
				(i)++;
			if (*(s + i) && *(s + i) == '\'')
				i++;
			else
				return (0);
		}
		else if (*(s + i) == '\"')
		{
			if (!ft_check_double_quote(&i, s))
				return (0);
		}
		else
			i++;
	}	
	return (1);
}

int	check_word(char *str)
{
	char	*meta;
	int		i;
	int		j;

	j = 0;
	meta = "><|";
	while (*(meta + j))
	{
		i = 0;
		while (*(str + i) == *(meta + j))
		{
			if (i >= 1 && *(meta + j) == '|')
				return (0);
			if (i >= 2 && (*(meta + j) == '>' || *(meta + j) == '<'))
				return (0);
			i++;
		}
		j++;
	}
	if (!check_nb_quote(str))
		return (0);
	return (1);
}
