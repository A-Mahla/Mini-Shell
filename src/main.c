/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 07:55:05 by meudier           #+#    #+#             */
/*   Updated: 2022/07/21 19:46:27 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	g_sigint_code = 0;

char	*get_line(void)
{
	char		*line;
	char		*buf;
	char		*prompt;
	char		*temp;

	buf = getcwd(NULL, 0);
	temp = ft_strjoin("$", buf);
	prompt = ft_strjoin(temp, "$ ");
	line = readline(prompt);
	if (line && *line)
		add_history(line);
	free(buf);
	free(temp);
	free(prompt);
	return (line);
}

void	init_vars(t_vars *vars)
{
	vars->var = NULL;
	vars->lst_parser = NULL;
	vars->pipe_info = NULL;
	vars->exit_code = 0;
}

void	minishell(char *line, t_vars *vars)
{
	t_lexer		*lst_lexer;
	t_parser	*lst_parser;
	t_pipe_info	pipe_info;

	lst_lexer = lexer(line, vars);
	free(line);
	if (!lst_lexer)
		return ;
	vars->lst_lexer = lst_lexer;
	pipe_info.pipes = get_pipes(lst_lexer, \
	&(pipe_info.num_of_process), vars);
	vars->pipe_info = &pipe_info;
	if (g_sigint_code == 1 || !parser(&lst_parser, lst_lexer, &pipe_info, vars))
	{
		g_sigint_code = 0;
		clear_err_pars(lst_lexer, lst_parser, &pipe_info);
		vars->exit_code = 2;
		return ;
	}
	vars->lst_parser = lst_parser;
	execute(lst_parser, &pipe_info, vars);
	close_std(lst_parser);
	lst_clear_parser(lst_parser);
	lst_clear_lexer(lst_lexer);
}

int	quit_proprely(t_vars *vars)
{
	lst_clear_envl(vars->envl);
	lst_clear_envl(vars->var);
	clear_history();
	write(1, "exit\n", 5);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_vars		vars;

	(void)av;
	if (ac == 1)
	{
		vars.envl = get_env(env, NULL);
		init_vars(&vars);
		while (1 && ac == 1)
		{
			sig_init();
			line = get_line();
			if (g_sigint_code == 3)
				vars.exit_code = 130;
			if (!line)
				return (quit_proprely(&vars));
			trim_line(line);
			if (*line)
				minishell(line, &vars);
		}
	}
	return (0);
}
