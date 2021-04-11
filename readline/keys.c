/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 16:29:15 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/06 13:55:24 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

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
	t_char	*prev;
	int		i;

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
	if (!(*list)->len)
		return ;
	(*list)->len--;
	s_read->cursor--;
	ft_putstr_fd("\033[1D\033[K", 1);
	delchar(list);
}

void	add_char(t_read *s_read, t_history **list, int c)
{
	s_read->cursor++;
	(*list)->len++;
	ft_putchar_fd(c, 1);
	addchar(list, c);
}

void	set_cursor_homee(t_read *s_read, t_history **list)
{
	int		col;
	int		row;
	int		len;
	float	div;
	int		sub;
	int		diff;

	diff = 0;
	row = s_read->pos.row - 1;
	col = s_read->pos.col - 1;
	len = s_read->pos.col + (*list)->len;
	div = (float)((float)len / (float)s_read->win.col);
	// printf("|%d||%d||%f|\n", len, s_read->win.col, div);
	if (div > floor(div) && floor(div))
		diff = floor(div) + 1;
	sub = (diff + s_read->pos.row) - s_read->win.row;
	if (sub > 0)
	{
		row -= diff;
		while (sub--)
			printf("\n");
		// s_read->pos.row = row;
	}
	s_read->cursor = 0;
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), col, row), 1);
	get_cursor(s_read);
	ft_putstr_fd(tgetstr("cd", NULL), 1);
}

void	up(t_read *s_read, t_history **list)
{
	t_char	*node;

	node = NULL;
	if (!*list)
		return ;
	if (s_read->key == key_u)
	{
		if (!(*list)->prev)
			return ;
		(*list) = (*list)->prev;
		set_cursor_homee(s_read, list);
		node = (*list)->str;
		while (node)
		{
			ft_putchar_fd(node->c, 1);
			node = node->next;
		}
	}
}

void	down(t_read *s_read, t_history **list)
{
	t_char	*node;

	node = NULL;
	if (!*list)
		return ;
	if (s_read->key == key_dw)
	{
		if (!(*list)->next)
			return ;
		(*list) = (*list)->next;
		set_cursor_homee(s_read, list);
		node = (*list)->str;
		while (node)
		{
			ft_putchar_fd(node->c, 1);
			node = node->next;
		}
	}
}
