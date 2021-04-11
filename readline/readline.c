/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:00:53 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/06 14:48:08 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	delete_node(t_history **hist)
{
	t_history	*prev;
	t_history	*last;

	last = NULL;
	prev = NULL;
	last = (*hist);
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	if (!prev)
	{
		free((*hist));
		*hist = NULL;
		return ;
	}
	if (prev)
	{
		prev->next = NULL;
		free(last);
		last = NULL;
	}
}

void	fill_input(t_read *s_read, t_history **list, t_history **hist)
{
	t_char	*node;
	int		i;

	i = 0;
	node = NULL;
	s_read->len = (*list)->len;
	s_read->input = (char *)malloc((*list)->len + 1);
	ft_bzero(s_read->input, (*list)->len + 1);
	node = (*list)->str;
	while (node)
	{
		s_read->input[i++] = node->c;
		node = node->next;
	}
	delete_node(hist);
}

void	readline(t_read *s_read, struct termios *term, t_history **hist)
{
	t_history	*list;
	t_history	*node;

	create_node(&node);
	list = add_node(hist, node);
	init_term(s_read, term);
	ft_putstr_fd("\033[1;32m➜ \033[1;34mreadline \033[0m", 1);
	get_cursor(s_read);
	while (1)
	{
		s_read->key = 0;
		read(0, &s_read->key, 3);
		termsize(s_read);
		if (s_read->key == key_u)
			up(s_read, &list);
		else if (s_read->key == key_dw)
			down(s_read, &list);
		else if (s_read->key > 31 && s_read->key < 127)
			add_char(s_read, &list, s_read->key);
		else if (s_read->key == 127)
			delete_char(s_read, &list);
		else if (s_read->key == 10)
			break ;
	}
	fill_input(s_read, &list, hist);
	get_cursor(s_read);
}

int	main(void)
{
	struct termios	term;
	t_read			s_read;
	t_history		*hist;

	fill_hist(&hist);
	while (1)
	{
		s_read = (t_read){0};
		readline(&s_read, &term, &hist);
		printf("\nlen : %d |%s|\n", s_read.len, s_read.input);
		history(&s_read, &hist);
		free(s_read.input);
		s_read.input = NULL;
	}
	return (0);
}
