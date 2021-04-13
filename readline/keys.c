/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 16:29:15 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/13 12:22:45 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_char(t_read *s_read, t_history **list, int c)
{
	t_char	*node;
	t_char	*last;

	node = NULL;
	last = NULL;
	node = (t_char *)malloc(sizeof(t_char));
	node->c = c;
	node->next = NULL;
	node->prev = NULL;
	(*list)->cursor++;
	(*list)->len++;
	printing(s_read, list, c);
	if (!(*list)->tmp)
		(*list)->tmp = node;
	else
	{
		last = (*list)->tmp;
		while (last->next)
			last = last->next;
		node->prev = last;
		last->next = node;
	}
}

void	printing(t_read *s_read, t_history **list, int c)
{
	int		diff;
	float	div;
	int		sub;
	int		row;

	ft_putchar_fd(c, 1);
	diff = 0;
	div = (float)((float)(*list)->cursor / (float)(s_read->win.col));
	if (div >= floor(div))
		diff = floor(div);
	row = s_read->pos.row;
	if (!(((*list)->cursor - diff) % s_read->win.col))
	{
		sub = (diff + s_read->pos.row) - s_read->win.row;
		row = s_read->pos.row + diff;
		if (sub > 0)
		{
			row = s_read->win.row;
			printf("\n");
			if (sub)
				s_read->pos.row--;
		}
		ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, row), 1);
	}
}

void	up(t_read *s_read, t_history **list)
{
	t_char	*node;

	node = NULL;
	if (!*list)
		return ;
	if (!(*list)->prev)
		return ;
	(*list) = (*list)->prev;
	cursor_home_clean(s_read, list);
	node = (*list)->tmp;
	while (node)
	{
		(*list)->cursor++;
		(*list)->len++;
		printing(s_read, list, node->c);
		node = node->next;
	}
}

void	down(t_read *s_read, t_history **list)
{
	t_char	*node;

	node = NULL;
	if (!*list)
		return ;
	if (!(*list)->next)
		return ;
	(*list) = (*list)->next;
	cursor_home_clean(s_read, list);
	node = (*list)->tmp;
	while (node)
	{
		(*list)->cursor++;
		(*list)->len++;
		printing(s_read, list, node->c);
		node = node->next;
	}
}
