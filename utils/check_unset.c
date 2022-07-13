/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:28:13 by amahla            #+#    #+#             */
/*   Updated: 2022/07/14 01:32:32 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	check_unset(char *str)
{
	int	i;

	i = 0;
	if (*(str + i) && !(ft_isalpha(*(str + i)) || *(str + i) == '_'))
		return (0);
	i++;
	while (*(str + i))
	{
		if (!ft_isalnum(*(str + i)))
			return (0);
		i++;
	}
	return (1);
}
