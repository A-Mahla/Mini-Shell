/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ammah <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:54:44 by ammah             #+#    #+#             */
/*   Updated: 2022/07/11 14:05:17 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	is_expand(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == '$' || *(str + i) == '\'' || *(str + i) == '\"')
			return (1);
		i++;
	}
	return (0);
}

int	get_word_expand(char *word, int *i, t_vars *vars, char *expand)
{
	int		size;
	int		y;
	char	*temp;

	size = 0;
	y = 0;
	(*i)++;
	while (*(word + *i + size) && ft_isalnum(*(word + *i + size)))
		size++;
	temp = cpy(get_var(word + *i, vars, size));
	(*i) += size;
	size = 0;
	while (*(temp + size))
	{
		*(expand + y) = *(temp + size);
		y++;
		size++;
	}
	free(temp);
	return (y);
}

int	simple_quote(char *word, int *i, char *expand)
{
	int	y;

	y = 0;
	(*i)++;
	while (*(word + *i) && *(word + *i) != '\'')
	{
		*(expand + y) = *(word + *i);
		(*i)++;
		y++;
	}
	if (*(word + *i) == '\'')
		(*i)++;
	return (y);
}

int	double_quote(char *word, int *i, t_vars *vars, char *expand)
{
	int	y;

	y = 0;
	(*i)++;
	while (*(word + *i) && *(word + *i) != '\"')
	{
		if (*(word + *i) == '$')
			y += get_word_expand(word, i, vars, expand + y);
		else
		{
			*(expand + y) = *(word + *i);
			(*i)++;
			y++;
		}
	}
	if (*(word + *i) == '\"')
		(*i)++;
	return (y);
}

void	get_expand(char **word, t_vars *vars, int size)
{
	int		i;
	int		y;
	char	*expand;

	i = 0;
	y = 0;
	expand = malloc((size + 1) * sizeof(char));
	if (!expand)
		return ;
	while (*word && (*word)[i])
	{
		if ((*word)[i] == '\'')
			y += simple_quote(*word, &i, expand + y);
		else if ((*word)[i] == '\"')
			y += double_quote(*word, &i, vars, expand + y);
		else if ((*word)[i] == '$')
			y += get_word_expand(*word, &i, vars, expand + y);
		else
			*(expand + y++) = (*word)[i++];
	}
	*(expand + y) = '\0';
	free(*word);
	*word = expand;
}
