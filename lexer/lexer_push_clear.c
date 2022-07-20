/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_push_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:08:30 by meudier           #+#    #+#             */
/*   Updated: 2022/07/20 10:13:42 by meudier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

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
