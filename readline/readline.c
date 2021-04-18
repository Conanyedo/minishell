/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:00:53 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/18 15:11:17 by ybouddou         ###   ########.fr       */
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
		else if (s_read->key == K_HOME || s_read->key == K_END)
			home_end(s_read, list);
		else if (s_read->key > 31 && s_read->key < 127)
			add_char(s_read, list, s_read->key);
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
