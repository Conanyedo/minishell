/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 16:29:15 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/12 13:42:52 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delchar(t_history **list)
{
	t_char	*node;
	t_char	*prev;

	node = NULL;
	prev = NULL;
	if (!(*list)->str)
		return ;
	node = (*list)->str;
	while (node->next)
	{
		prev = node;
		node = node->next;
	}
	if (prev)
	{
		prev->next = NULL;
		free(node);
	}
	else if (!prev)
	{
		free((*list)->str);
		(*list)->str = NULL;
	}
}

void	addchar(t_history **list, int c)
{
	t_char	*node;
	t_char	*last;

	node = NULL;
	last = NULL;
	node = (t_char *)malloc(sizeof(t_char));
	node->c = c;
	node->next = NULL;
	node->prev = NULL;
	if (!(*list)->str)
		(*list)->str = node;
	else
	{
		last = (*list)->str;
		while (last->next)
			last = last->next;
		node->prev = last;
		last->next = node;
	}
}

void	delete_char(t_read *s_read, t_history **list)
{
	int		diff;
	float	div;
	int		row;

	if (!(*list)->len)
		return ;
	diff = 0;
	(*list)->len--;
	(*list)->cursor--;
	div = (float)((float)(*list)->cursor / (float)(s_read->win.col));
	if (div >= floor(div))
		diff = floor(div);
	if (diff)
		diff--;
	if (!(((*list)->cursor - diff) % s_read->win.col))
	{
		row = s_read->pos.row + diff;
		ft_putstr_fd(tgoto(tgetstr("cm", NULL), s_read->win.col, row), 1);
		ft_putstr_fd(tgetstr("cd", NULL), 1);
	}
	else
		ft_putstr_fd("\033[1D\033[K", 1);
	delchar(list);
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

void	add_char(t_read *s_read, t_history **list, int c)
{
	(*list)->cursor++;
	(*list)->len++;
	printing(s_read, list, c);
	addchar(list, c);
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
	node = (*list)->str;
	while (node)
	{
		(*list)->cursor++;
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
	node = (*list)->str;
	while (node)
	{
		(*list)->cursor++;
		printing(s_read, list, node->c);
		node = node->next;
	}
}

void	left(t_read *s_read, t_history **list)
{
	t_char	*node;

	node = NULL;
	if (!*list)
		return ;
	if (!(*list)->str->prev)
		return ;
	(*list) = (*list)->next;
	cursor_home_clean(s_read, list);
	node = (*list)->str;
	while (node)
	{
		(*list)->cursor++;
		printing(s_read, list, node->c);
		node = node->next;
	}
}

void	right(t_read *s_read, t_history **list)
{
	t_char	*node;

	node = NULL;
	if (!*list)
		return ;
	if (!(*list)->next)
		return ;
	(*list) = (*list)->next;
	cursor_home_clean(s_read, list);
	node = (*list)->str;
	while (node)
	{
		(*list)->cursor++;
		printing(s_read, list, node->c);
		node = node->next;
	}
}
