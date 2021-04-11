/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 18:28:31 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/10 12:14:28 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	create_node(t_history **node)
{
	(*node) = NULL;
	(*node) = (t_history *)malloc(sizeof(t_history));
	(*node)->next = NULL;
	(*node)->prev = NULL;
	(*node)->str = NULL;
	(*node)->cursor = 0;
	(*node)->len = 0;
}

void	create_chars(t_history **node, char *line)
{
	t_char		*charlist;

	charlist = NULL;
	(*node)->str = (t_char *)malloc(sizeof(t_char));
	(*node)->str->next = NULL;
	(*node)->str->prev = NULL;
	charlist = (*node)->str;
	while (line[(*node)->len])
	{
		charlist->c = line[(*node)->len];
		(*node)->len++;
		if (!line[(*node)->len])
			break ;
		charlist->next = (t_char *)malloc(sizeof(t_char));
		charlist->next->prev = charlist;
		charlist = charlist->next;
	}
	charlist->next = NULL;
}

void	fill_hist(t_history **hist)
{
	t_history	*node;
	int			fd;
	char		*line;

	*hist = NULL;
	fd = open("/Users/ybouddou/.minishell_history", O_RDWR | O_CREAT, 0666);
	while (get_next_line(fd, &line) > 0)
	{
		create_node(&node);
		create_chars(&node, line);
		free(line);
		add_node(hist, node);
	}
	free(line);
	close(fd);
}

void	fill_file(t_history **hist, int fd)
{
	t_char		*charlist;
	t_history	*last;

	last = NULL;
	charlist = NULL;
	last = NULL;
	last = (*hist);
	while (last)
	{
		charlist = NULL;
		charlist = last->str;
		while (charlist)
		{
			write(fd, &charlist->c, 1);
			charlist = charlist->next;
		}
		write(fd, "\n", 1);
		last = last->next;
	}
}

void	history(t_read *s_read, t_history **hist)
{
	t_history	*node;
	int			fd;

	node = NULL;
	if (!s_read->len)
		return ;
	fd = open("/Users/ybouddou/.minishell_history", O_RDWR | O_TRUNC);
	close(fd);
	fd = open("/Users/ybouddou/.minishell_history", O_RDWR | O_APPEND);
	create_node(&node);
	create_chars(&node, s_read->input);
	add_node(hist, node);
	fill_file(hist, fd);
	close(fd);
}
