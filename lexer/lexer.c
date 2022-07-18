/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:03:05 by maxenceeudi       #+#    #+#             */
/*   Updated: 2022/07/18 12:40:25 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	cmp_and_push(char **words, t_lexer **lst, int i, t_vars *vars)
{
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
		cmp_and_push(words, &lst, i++, vars);
	clear_tab(words);
	return (lst);
}

int	get_num_of_arg(t_lexer *lexer)
{
	t_lexer	*temp;
	int		i;

	i = 0;
	temp = lexer;
	while (temp && (temp->type == WRD || temp->type == EMPTY))
	{
		while (temp && temp->type == EMPTY)
			temp = temp->next;
		if (temp)
		{
			temp = temp->next;
			i++;
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

void	push_lexer(t_lexer **lst, char *word, int TYPE, t_vars *vars)
{
	t_lexer	*new;
	t_lexer	*last;

	
	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		error_malloc_lexer(*lst, vars);
	new->data = cpy(word);
	new->type = TYPE;
	new->prev = NULL;
	new->next = NULL;
	if (!*lst)
	{
		new->prev = NULL;
		*lst = new;
	}	
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
		new->prev = last;
	}
}

void	lst_clear_lexer(t_lexer *lexer)
{
	t_lexer	*temp;
	t_lexer	*last;

	last = lexer;
	while (last)
	{
		temp = last;
		last = last->next;
		free(temp->data);
		temp->data = NULL;
		temp->type = 0;
		free(temp);
		temp = NULL;
	}
}
