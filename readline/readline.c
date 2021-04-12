/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:00:53 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/12 13:44:48 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (!prev)
	{
		free_str(&(*hist)->str);
		free((*hist));
		*hist = NULL;
		return ;
	}
	if (prev)
	{
		prev->next = NULL;
		free_str(&last->str);
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

void	keys(t_mini *mini, t_read *s_read, t_history **list)
{
	// int		fd;

	get_cursor(s_read, list);
	while (1)
	{
		s_read->key = 0;
		read(0, &s_read->key, 4);
		// fd = open("file", O_RDWR | O_CREAT | O_TRUNC, 0666);
		// ft_putnbr_fd(s_read->key&0xFF, fd);
		// ft_putchar_fd('|', fd);
		// ft_putnbr_fd((s_read->key >> 8)&0xFF, fd);
		// ft_putchar_fd('|', fd);
		// ft_putnbr_fd((s_read->key >> 16)&0xFF, fd);
		// ft_putchar_fd('\n', fd);
		// ft_putchar_fd(s_read->key&0xFF, fd);
		// ft_putchar_fd('|', fd);
		// ft_putchar_fd((s_read->key >> 8)&0xFF, fd);
		// ft_putchar_fd('|', fd);
		// ft_putchar_fd((s_read->key >> 16)&0xFF, fd);
		termsize(s_read);
		if (s_read->key == KU)
			up(s_read, list);
		else if (s_read->key == KDW)
			down(s_read, list);
		else if (s_read->key == K_HOME)
			set_cursor_home(s_read);
		else if (s_read->key == K_END)
			set_cursor_end(s_read, list);
		else if (s_read->key > 31 && s_read->key < 127)
			add_char(s_read, list, s_read->key);
		else if (s_read->key == 127)
			delete_char(s_read, list);
		else if (s_read->key == 12)
			clear_term(mini, s_read, list);
		else if (s_read->key == 3) // ctrl-C
			ctrl_c(mini, s_read, list);
		// else if (s_read->key == 28)// ctrl-\\*
		// 	clear_term(s_read);
		else if (s_read->key == 4) // ctrl-d*
			ctrl_d(list);
		else if (s_read->key == 10)
			break ;
		// else
		// 	ft_putchar_fd('+', fd);
		// close(fd);
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
	create_node(&node);
	list = add_node(hist, node);
	init_term(&s_read, term);
	keys(mini, &s_read, &list);
	fill_input(&s_read, &list, hist);
	history(&s_read, hist);
	ft_putchar_fd('\n', 1);
	(*term).c_lflag |= (ISIG);
	tcsetattr(0, TCSANOW, term);
	return (s_read.input);
}
