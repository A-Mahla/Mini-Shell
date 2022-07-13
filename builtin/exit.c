/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ammah <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:57:12 by ammah             #+#    #+#             */
/*   Updated: 2022/07/13 18:51:46 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (*(str + i) == '-')
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

int	check_code(t_parser *parser, int *is_exit, int pipe)
{
	while (ft_strcmp(parser->cmd, "exit") != 0)
		parser = parser->next;
	if (!pipe)
		write(1, "exit\n", 5);
	if (nb_of_arg(parser->arg) > 2 && check_arg(parser->arg[1]))
	{
		printf("minishell: exit: too many arguments\n");
		*is_exit = 0;
	}
	else if ((nb_of_arg(parser->arg) > 1 && !check_arg(parser->arg[1]))
		|| (nb_of_arg(parser->arg) == 2 && (ft_ltoi(parser->arg[1]) > LONG_MAX
				|| ft_strlen(parser->arg[1]) > 20)))
	{
		printf("minishell: exit: %s: numeric argument required\n", parser->arg[1]);
		return (1);
	}
	else if (nb_of_arg(parser->arg) == 2)
		return (convert_nb(ft_ltoi(parser->arg[1]), parser->arg[1]));
	return (0);
}
		
int	ft_exit(t_vars *vars, int *built, int pipe)
{
	int	is_exit;
	int	exit_code;

	is_exit = 1;
	*built = 1;
	exit_code = check_code(vars->lst_parser, &is_exit, pipe);
	if (!is_exit)
		return (0);
	if (vars->pipe_info->pipes)
		close_pipes(vars->pipe_info);
	close_std(vars->lst_parser);
	lst_clear_parser(vars->lst_parser);
	lst_clear_lexer(vars->lst_lexer);
	lst_clear_envl(vars->envl);
	lst_clear_envl(vars->var);
	clear_history();
	exit(exit_code);
}
