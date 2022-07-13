/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:28:13 by amahla            #+#    #+#             */
/*   Updated: 2022/07/14 00:22:14 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	check_export(char *str)
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
