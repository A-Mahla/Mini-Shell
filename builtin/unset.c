/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:37:59 by meudier           #+#    #+#             */
/*   Updated: 2022/07/12 12:49:05 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void    unset(t_parser *parser, int *built, t_vars *vars)
{
    int i;

    *built = 1;
    if (!parser->arg[1])
        return ;
    i = 1;
    while (parser->arg[i])
    {
        remove_if(parser->arg[i], &(vars->envl), &ft_strcmp);
        remove_if(parser->arg[i], &(vars->var), &ft_strcmp);
        i++;
    }
}
