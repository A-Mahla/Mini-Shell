/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:54:44 by ammah             #+#    #+#             */
/*   Updated: 2022/07/22 10:14:32 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

char	*get_word_expand_2(char *word, int *i, t_vars *vars)
{
	int		size;
	char	*temp;

	size = 0;
	while (*(word + *i + size) && (ft_isalnum(*(word + *i + size))
			|| *(word + *i + size) == '_'))
		size++;
	temp = cpy(get_var(word + *i, vars, size));
	(*i) += size;
	return (temp);
}
