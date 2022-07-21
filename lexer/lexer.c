/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:03:05 by maxenceeudi       #+#    #+#             */
/*   Updated: 2022/07/21 11:05:59 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	cmp_and_push(char **words, t_lexer **lst, int i, t_vars *vars)
{	
	if (!check_word(words[i]))
	{
		write(2, "minishell: syntax error\n", 24);
		vars->exit_code = 2;
		lst_clear_lexer(*lst);
		*lst = NULL;
		return (1);
	}
	if (ft_strcmp(words[i], "") == 0)
		push_lexer(lst, words[i], EMPTY, vars);
	if (is_expand(words[i]))
		ft_expand(words + i, vars, *lst);
	if (ft_strcmp(words[i], "|") == 0)
		push_lexer(lst, words[i], PIPE, vars);
	else if (ft_strcmp(words[i], "<") == 0)
		push_lexer(lst, words[i], REDIR_IN, vars);
	else if (ft_strcmp(words[i], ">") == 0)
		push_lexer(lst, words[i], REDIR_OUT, vars);
	else if (ft_strcmp(words[i], ">>") == 0)
		push_lexer(lst, words[i], REDIR_OUT_APPEND, vars);
	else if (ft_strcmp(words[i], "<<") == 0)
		push_lexer(lst, words[i], HERDOC, vars);
	else
		push_lexer(lst, words[i], WRD, vars);
	return (0);
}

t_lexer	*lexer(char *line, t_vars *vars)
{
	char	**words;
	t_lexer	*lst;
	int		i;

	i = 0;
	lst = NULL;
	words = ft_split_lexer(line);
	if (!words)
		return (NULL);
	while (words[i])
		if (cmp_and_push(words, &lst, i++, vars))
			break ;
	clear_tab(words);
	return (lst);
}

int	get_num_of_arg(t_lexer *lexer)
{
	int		i;

	i = 0;
	while (lexer && lexer->type != PIPE)
	{
		while (lexer && lexer->type == WRD)
		{
			lexer = lexer->next;
			i++;
		}
		if (lexer && !(lexer->type == WRD || lexer->type == PIPE))
		{
			if (lexer->type == EMPTY)
				lexer = lexer->next;
			else if (lexer->next)
				lexer = lexer->next->next;
			else
				lexer = lexer->next;
		}
	}
	return (i);
}

char	*get_var(char *str, t_vars *vars, int size)
{
	t_env	*last_env;
	t_env	*last_var;
	char	*temp;

	last_env = vars->envl;
	last_var = vars->var;
	temp = cpy_2(str, size);
	while (last_env)
	{
		if (ft_strcmp(temp, last_env->key) == 0)
		{
			free(temp);
			return (last_env->value);
		}
		last_env = last_env->next;
	}
	while (last_var)
	{
		if (ft_strcmp(temp, last_var->key) == 0)
		{
			free(temp);
			return (last_var->value);
		}
		last_var = last_var->next;
	}
	free(temp);
	return ("");
}
