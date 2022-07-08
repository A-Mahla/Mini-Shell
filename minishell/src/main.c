/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 07:55:05 by meudier           #+#    #+#             */
/*   Updated: 2022/07/08 12:34:22 by meudier          ###   ########.fr       */
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
	temp = ft_strjoin("\033[0;32m", buf);
	write (1, "\033[0;32m", 9);
	prompt = ft_strjoin(temp, "$ \033[0m");
	line = readline(prompt);
	if (line && *line)
		add_history(line);

	free(buf);
	free(temp);
	free(prompt);
	return (line);
}

int	exit_shell(char *line, t_lexer *lst_lexer, t_vars *vars)
{
	free(line);
	lst_clear_lexer(lst_lexer);
	lst_clear_envl(vars->envl);
	lst_clear_envl(vars->var);
	clear_history();
	exit (0);
}

void	minishell(char *line, t_vars *vars)
{
	t_lexer		*lst_lexer;
	t_parser	*lst_parser;
	t_pipe_info	pipe_info;

	lst_lexer = lexer(line, vars);
	if (ft_strcmp(lst_lexer->data, "exit") == 0)
		exit_shell(line, lst_lexer, vars);
	pipe_info.pipes = get_pipes(lst_lexer, &(pipe_info.num_of_process));
	lst_parser = parser(lst_lexer, &pipe_info);
	execute(lst_parser, &pipe_info, vars);
	lst_clear_parser(lst_parser);
	lst_clear_lexer(lst_lexer);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_vars		vars;

	(void)av;
	vars.var = NULL;
	vars.envl = get_env(env);
	sig_init();
	while (1 && ac == 1)
	{
		line = get_line();
		if (!line)
			return (1);
		if (*line)
			minishell(line, &vars);
		free(line);
	}
	return (0);
}	
