/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 18:28:31 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/13 13:57:36 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_node(t_history **node, int rank)
{
	(*node) = NULL;
	(*node) = (t_history *)malloc(sizeof(t_history));
	(*node)->next = NULL;
	(*node)->prev = NULL;
	(*node)->str = NULL;
	(*node)->tmp = NULL;
	(*node)->rank = rank;
	(*node)->cursor = 0;
	(*node)->len = 0;
}

void	create_chars(t_history *node, t_char **str, char *line)
{
	t_char		*charlist;
	int			len;

	charlist = NULL;
	len = node->len;
	(*str) = (t_char *)malloc(sizeof(t_char));
	(*str)->next = NULL;
	(*str)->prev = NULL;
	charlist = (*str);
	while (line[len])
	{
		charlist->c = line[len];
		len++;
		if (!line[len])
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
	char		*tmp;

	*hist = NULL;
	tmp = ft_strdup(ft_lstsearch(g_mini->myenv, "HOME", &g_mini->print));
	g_mini->home = ft_strjoin(tmp, "/.minishell_history");
	free(tmp);
	fd = open(g_mini->home, O_RDWR | O_CREAT, 0666);
	while (get_next_line(fd, &line) > 0)
	{
		create_node(&node, 0);
		create_chars(node, &node->str, line);
		create_chars(node, &node->tmp, line);
		free(line);
		add_node(hist, node);
	}
	free(line);
	close(fd);
}

void	fill_file(t_history **node, int fd)
{
	t_char		*charlist;

	charlist = NULL;
	charlist = (*node)->tmp;
	while (charlist)
	{
		write(fd, &charlist->c, 1);
		if (!charlist->next)
			write(fd, "\n", 1);
		charlist = charlist->next;
	}
}

void	history(t_read *s_read, t_history **hist)
{
	t_history	*node;
	int			fd;

	node = NULL;
	if (!s_read->len)
		return ;
	fd = open(g_mini->home, O_RDWR | O_APPEND);
	create_node(&node, 0);
	create_chars(node, &node->str, s_read->input);
	create_chars(node, &node->tmp, s_read->input);
	add_node(hist, node);
	fill_file(&node, fd);
	close(fd);
}
