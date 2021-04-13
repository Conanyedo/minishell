/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 17:25:56 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/13 12:22:26 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_str(t_char *node, t_char **dup)
{
	t_char	*list;
	t_char	*last;

	(*dup) = NULL;
	(*dup) = (t_char *)malloc(sizeof(t_char));
	(*dup)->next = NULL;
	(*dup)->prev = NULL;
	last = node;
	list = (*dup);
	while (last)
	{
		list->c = last->c;
		last = last->next;
		if (!last)
			break ;
		list->next = (t_char *)malloc(sizeof(t_char));
		list->next->prev = list;
		list = list->next;
	}
	list->next = NULL;
}

void	set_cursor_home(t_read *s_read)
{
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), s_read->pos.col,
			s_read->pos.row), 1);
}

void	cursor_home_clean(t_read *s_read, t_history **list)
{
	(*list)->cursor = s_read->pos.col;
	(*list)->len = 0;
	set_cursor_home(s_read);
	ft_putstr_fd(tgetstr("cd", NULL), 1);
}

t_history	*add_node(t_history **hist, t_history *node)
{
	t_history	*last;

	if (!(*hist))
	{
		(*hist) = node;
		return (*hist);
	}
	else
	{
		last = NULL;
		last = (*hist);
		while (last->next)
			last = last->next;
		node->prev = last;
		last->next = node;
		return (last->next);
	}
}
