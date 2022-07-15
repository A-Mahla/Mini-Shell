/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:37:59 by meudier           #+#    #+#             */
/*   Updated: 2022/07/14 00:55:33 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int pwd(t_parser *parser, int *built)
{
    char    *temp;

    *built = 1;
    temp = getcwd(NULL, 0);
	if (!temp)
		return (1);
    write(parser->stdout, temp, ft_strlen(temp));
    write(parser->stdout, "\n", 1);
    free(temp);
    return (0);
}
