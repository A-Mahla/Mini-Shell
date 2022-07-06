/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 18:03:05 by maxenceeudi       #+#    #+#             */
/*   Updated: 2022/07/04 11:26:51 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	cmp_and_push(char **words, t_lexer **lst, int i)
{
	if (ft_strcmp(words[i], "|") == 0)
		push_lexer(lst, words[i], PIPE);
	else if (ft_strcmp(words[i], "<") == 0)
		push_lexer(lst, words[i], REDIR_IN);
	else if (ft_strcmp(words[i], ">") == 0)
		push_lexer(lst, words[i], REDIR_OUT);
	else if (ft_strcmp(words[i], ">>") == 0)
		push_lexer(lst, words[i], REDIR_OUT_APPEND);
	else if (ft_strcmp(words[i], "<<") == 0)
		push_lexer(lst, words[i], HERDOC);
	else if (ft_strcmp(words[i], "") == 0)
		push_lexer(lst, words[i], EMPTY);
	else
		push_lexer(lst, words[i], WRD);
}

t_lexer	*lexer(char *line)
{
	char	**words;
	t_lexer	*lst;
	int		i;

	i = 0;
	lst = NULL;
	words = ft_split_lexer(line);
	while (words[i])
		cmp_and_push(words, &lst, i++);
	clear_tab(words);
	return (lst);
}

int	get_num_of_arg(t_lexer *lexer)
{
	t_lexer	*temp;
	int		i;

	i = 0;
	temp = lexer;
	while (temp && temp->type == WRD)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	push_lexer(t_lexer **lst, char *word, int TYPE)
{
	t_lexer	*new;
	t_lexer	*last;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		exit (1);
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
