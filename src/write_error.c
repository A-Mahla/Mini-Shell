/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:44:17 by meudier           #+#    #+#             */
/*   Updated: 2022/07/19 09:48:43 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	write_error(char *cmd)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin("minishell: command not found: ", cmd);
	temp2 = ft_strjoin(temp1, "\n");
	write (2, temp2, 31 + ft_strlen(cmd));
	free(temp2);
	free(temp1);
}

void	write_is_a_directory(char *cmd)
{
	char	*temp1;

	temp1 = ft_strjoin(cmd, ": is a directory\n");
	write (2, temp1, 17 + ft_strlen(cmd));
	free(temp1);
}