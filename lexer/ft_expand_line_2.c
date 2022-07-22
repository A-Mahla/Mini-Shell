/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_line_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:54:44 by ammah             #+#    #+#             */
/*   Updated: 2022/07/22 12:28:47 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	is_expand_line(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == '$')
			return (1);
		i++;
	}
	return (0);
}

int	get_word_expand_line(char *word, int *i, t_vars *vars, char *expand)
{
	int		size;
	int		y;
	char	*temp;

	size = 0;
	y = 0;
	(*i)++;
	if (ft_strncmp(word + *i, "\"\"", 2) == 0
		|| ft_strncmp(word + *i, "\'\'", 2) == 0)
	{
		*i = *i + 2;
		return (y);
	}
	if (*(word + *i) == '?')
	{
		temp = ft_itoa(vars->exit_code);
		(*i)++;
	}
	else
		temp = get_word_expand_2(word, i, vars);
	while (*(temp + size))
		*(expand + y++) = *(temp + size++);
	free(temp);
	return (y);
}

int	simple_quote_line(char *word, int *i, char *expand)
{
	int	y;

	y = 0;
	*(expand + y) = *(word + *i);
	(*i)++;
	y++;
	while (*(word + *i) && *(word + *i) != '\'')
	{
		*(expand + y) = *(word + *i);
		(*i)++;
		y++;
	}
	if (*(word + *i) == '\'')
	{
		*(expand + y) = *(word + *i);
		(*i)++;
		y++;
	}
	return (y);
}

int	double_quote_line(char *word, int *i, char *expand)
{
	int	y;

	y = 0;
	*(expand + y) = *(word + *i);
	(*i)++;
	y++;
	while (*(word + *i) && *(word + *i) != '\"')
	{
		*(expand + y) = *(word + *i);
		(*i)++;
		y++;
	}
	if (*(word + *i) == '\"')
	{
		*(expand + y) = *(word + *i);
		(*i)++;
		y++;
	}
	return (y);
}

void	get_expand_line(char **word, t_vars *vars, int size, t_lexer *lst)
{
	int		i;
	int		y;
	char	*expand;

	i = 0;
	y = 0;
	expand = malloc((size + 1) * sizeof(char));
	if (!expand)
		error_malloc_lexer(lst, vars);
	while (*word && (*word)[i])
	{
		if ((*word)[i] == '\'')
			y += simple_quote_line(*word, &i, expand + y);
		else if ((*word)[i] == '\"')
			y += double_quote_line(*word, &i, expand + y);
		else if ((*word)[i] == '$' && (*word)[i + 1] && ((*word)[i] == '_'
			|| ft_isalnum((*word)[i + 1]) || (*word)[i + 1] == '?'
			|| (*word)[i + 1] == '\'' || (*word)[i + 1] == '\"'))
			y += get_word_expand_line(*word, &i, vars, expand + y);
		else
			*(expand + y++) = (*word)[i++];
	}
	*(expand + y) = '\0';
	free(*word);
	*word = expand;
}
