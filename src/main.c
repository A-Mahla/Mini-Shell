/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 07:55:05 by meudier           #+#    #+#             */
/*   Updated: 2022/07/15 14:37:26 by ammah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"


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
	vars->lst_lexer = lst_lexer;
	pipe_info.pipes = get_pipes(lst_lexer, &(pipe_info.num_of_process));
	lst_parser = parser(lst_lexer, &pipe_info);
	vars->lst_parser = lst_parser;
	vars->pipe_info = &pipe_info;
	execute(lst_parser, &pipe_info, vars);
	lst_clear_parser(lst_parser);
	lst_clear_lexer(lst_lexer);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_vars		vars;

	(void)av;
	vars.envl = get_env(env, NULL);
	init_vars(&vars);
	sig_init();
	while (1 && ac == 1)
	{
		line = get_line();
		if (!line)
			return (1);
		if (*line)
			minishell(line, &vars);
	}
	return (0);
}	
