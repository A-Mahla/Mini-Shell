/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:41:26 by amahla            #+#    #+#             */
/*   Updated: 2022/07/21 12:06:12 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	error_exit(t_parser *parser)
{
	write(2, "minishell: exit: ", 17);
	write(2, parser->arg[1], ft_strlen(parser->arg[1]));
	write(2, ": numeric argument required\n", 28);
}
