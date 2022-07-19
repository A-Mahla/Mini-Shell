/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:57:12 by ammah             #+#    #+#             */
/*   Updated: 2022/07/19 18:24:20 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (*(str + i) == '-' || *(str + i) == '+')
		i++;
	while (*(str + i))
	{
		if (!ft_isdigit(*(str + i)))
			return (0);
		i++;
	}
	return (1);
}

int	nb_of_arg(char **cmd)
{
	int	i;

	i = 0;
	while (*cmd && cmd[i])
		i++;
	return (i);
}

int	convert_nb(unsigned long nb, char *arg)
{
	nb = nb % 256;
	if (arg[0] == '-' && nb)
		nb = 256 - nb;
	return ((int)nb);
}

int	check_code(t_parser *parser, int *is_exit, int pipe, t_vars *vars)
{
	while (ft_strcmp(parser->cmd, "exit") != 0)
		parser = parser->next;
	if (!pipe)
		write(1, "exit\n", 5);
	if (nb_of_arg(parser->arg) > 2 && check_arg(parser->arg[1]))
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		*is_exit = 0;
	}
	else if ((nb_of_arg(parser->arg) > 1 && !check_arg(parser->arg[1]))
			|| (nb_of_arg(parser->arg) == 2 && ((ft_ltoi(parser->arg[1]) > LONG_MAX
				&& parser->arg[1][0] != '-')
			|| (ft_ltoi(parser->arg[1]) > ULONG_MAX - LONG_MAX
				&& parser->arg[1][0] == '-')
			|| ft_strlen(ft_check_zero(parser->arg[1])) > 21)))
	{
		write(2, "minishell: exit: ", 17);
		write(2, parser->arg[1], ft_strlen(parser->arg[1]));
		write(2, ": numeric argument required\n", 28);
		return (2);
	}
	else if (nb_of_arg(parser->arg) == 2)
		return (convert_nb(ft_ltoi(parser->arg[1]), parser->arg[1]));
	else
		return (vars->exit_code);
	return (1);
}

int	ft_exit(t_vars *vars, int *built, int pipe)
{
	int	is_exit;
	int	exit_code;

	is_exit = 1;
	*built = 1;
	exit_code = check_code(vars->lst_parser, &is_exit, pipe, vars);
	if (!is_exit)
		return (1);
	if (vars->pipe_info->pipes)
		close_pipes(vars->pipe_info);
	close_std(vars->lst_parser);
	if (pipe)
	{
		close(0);
		close(1);
		close(2);
	}
	lst_clear_parser(vars->lst_parser);
	lst_clear_lexer(vars->lst_lexer);
	lst_clear_envl(vars->envl);
	lst_clear_envl(vars->var);
	clear_history();
	exit(exit_code);
}
