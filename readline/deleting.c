/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 12:06:30 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/13 12:09:53 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delchar(t_history **list)
{
	t_char	*node;
	t_char	*prev;

	node = NULL;
	prev = NULL;
	if (!(*list)->tmp)
		return ;
	node = (*list)->tmp;
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
		free((*list)->tmp);
		(*list)->tmp = NULL;
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

void	free_str(t_char	**node)
{
	t_char	*list;
	t_char	*prev;

	list = *node;
	while (list)
	{
		prev = list;
		list = list->next;
		free(prev);
	}
	*node = NULL;
}

void	delete_head(t_history **hist)
{
	free_str(&(*hist)->str);
	free_str(&(*hist)->tmp);
	free((*hist));
	*hist = NULL;
}

void	delete_node(t_history **hist)
{
	t_history	*prev;
	t_history	*last;

	last = NULL;
	prev = NULL;
	if (!(*hist))
		return ;
	last = (*hist);
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	if (prev)
	{
		prev->next = NULL;
		free_str(&last->str);
		free_str(&last->tmp);
		free(last);
		last = NULL;
		return ;
	}
	delete_head(hist);
}
