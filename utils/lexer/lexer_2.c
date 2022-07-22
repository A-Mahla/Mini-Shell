/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:02:23 by meudier           #+#    #+#             */
/*   Updated: 2022/07/21 11:06:32 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h" 

int	check_nb_quote(char *str)
{
	int	nb_qt;
	int	i;

	i = 0;
	nb_qt = 0;
	if (str[i] == '\'' || str[i] == '\"')
	{
		while (str[i])
			if (str[i++] == str[0])
				nb_qt++;
		if (nb_qt % 2 != 0)
			return (0);
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
