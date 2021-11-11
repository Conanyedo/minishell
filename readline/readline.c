/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:00:53 by ybouddou          #+#    #+#             */
/*   Updated: 2021/05/07 16:24:19 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_input(t_read *s_read, t_history **list, t_history **hist)
{
	t_char	*node;
	int		i;

	i = 0;
	node = NULL;
	s_read->len = (*list)->len;
	s_read->input = (char *)malloc((*list)->len + 1);
	ft_bzero(s_read->input, (*list)->len + 1);
	node = (*list)->tmp;
	while (node)
	{
		s_read->input[i++] = node->c;
		node = node->next;
	}
	if (!(*list)->rank)
	{
		free_str(&(*list)->tmp);
		dup_str((*list)->str, &(*list)->tmp);
	}
	delete_node(hist);
}

void	char_node(t_history **list)
{
	(*list)->tmp = (t_char *)malloc(sizeof(t_char));
	(*list)->tmp->c = 0;
	(*list)->tmp->next = NULL;
	(*list)->tmp->prev = NULL;
}

void	right(t_read *s_read, t_history **list)
{
	if ((*list)->cursor == ((*list)->len + s_read->pos.col))
		return ;
	(*list)->cursor++;
	ft_putstr_fd("\033[1C", 1);
}

void	left(t_read *s_read, t_history **list)
{
	if ((*list)->cursor == s_read->pos.col)
		return ;
	(*list)->cursor--;
	ft_putstr_fd("\033[1D", 1);
}

void	add_charsss(t_read *s_read, t_history **list)
{
	t_char	*node;
	t_char	*last;
	t_char	*prev;
	int		i;
	int		len;

	node = NULL;
	last = NULL;
	prev = NULL;
	node = (t_char *)malloc(sizeof(t_char));
	node->c = s_read->key;
	node->next = NULL;
	node->prev = NULL;
	i = s_read->pos.col;
	if (!(*list)->tmp)
		(*list)->tmp = node;
	else
	{
		i = s_read->pos.col;
		last = (*list)->tmp;
		while (i < (*list)->cursor)
		{
			prev = last;
			last = last->next;
			i++;
		}
		node->next = last;
		node->prev = prev;
		if (prev)
			prev->next = node;
		if (!prev)
			(*list)->tmp = node;
	}
	(*list)->cursor++;
	(*list)->len++;
	last = node;
	while (last)
	{
		printing(s_read, list, last->c);
		last = last->next;
	}
	len = (*list)->len + s_read->pos.col;
	while (--len > i)
		ft_putstr_fd("\033[1D", 1);
}

void	keys(t_mini *mini, t_read *s_read, t_history **list)
{
	get_cursor(s_read, list);
	while (1)
	{
		s_read->key = 0;
		read(0, &s_read->key, 4);
		termsize(s_read);
		if (s_read->key == KU)
			up(s_read, list);
		else if (s_read->key == KDW)
			down(s_read, list);
		else if (s_read->key == KL)
			left(s_read, list);
		else if (s_read->key == KR)
			right(s_read, list);
		else if (s_read->key == K_HOME || s_read->key == K_END)
			home_end(s_read, list);
		else if (s_read->key > 31 && s_read->key < 127)
			add_charsss(s_read, list);
		// else if (s_read->key > 31 && s_read->key < 127)
		// 	add_char(s_read, list, s_read->key);
		else if (s_read->key == 127)
			delete_char(s_read, list);
		else if (s_read->key == 3)
			ctrl_c(mini, s_read, list);
		else if (s_read->key == 4)
			ctrl_d(list);
		else if (s_read->key == 10)
			break ;
	}
}

char	*readline(t_mini *mini, t_history **hist, struct termios *term)
{
	t_read			s_read;
	t_history		*list;
	t_history		*node;

	s_read.pos = (t_pos){0};
	s_read.win = (t_pos){0};
	s_read = (t_read){0};
	create_node(&node, 1);
	list = add_node(hist, node);
	init_term(term);
	keys(mini, &s_read, &list);
	fill_input(&s_read, &list, hist);
	history(&s_read, hist);
	ft_putchar_fd('\n', 1);
	(*term).c_lflag |= (ISIG);
	tcsetattr(0, TCSANOW, term);
	return (s_read.input);
}
