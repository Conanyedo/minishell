/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 17:25:56 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/11 13:43:00 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	clear_term(t_mini *mini, t_read *s_read, t_history **list)
{
	t_char	*node;

	node = NULL;
	ft_putstr_fd(s_read->clear, 1);
	prompt(mini);
	get_cursor(s_read, list);
	node = (*list)->str;
	while (node)
	{
		(*list)->cursor++;
		printing(s_read, list, node->c);
		node = node->next;
	}
}

void	set_cursor_end(t_read *s_read, t_history **list)
{
	int		diff;
	float	div;
	int		mod;

	diff = 0;
	div = (float)((float)(*list)->cursor / (float)(s_read->win.col));
	if (div > floor(div))
		diff = floor(div);
	mod = ((*list)->cursor - diff) % s_read->win.col;
	if ((s_read->win.col - diff) <= mod)
	{
		diff--;
		mod++;
	}
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), mod, s_read->pos.row + diff), 1);
}

void	set_cursor_home(t_read *s_read)
{
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), s_read->pos.col,
			s_read->pos.row), 1);
}

void	cursor_home_clean(t_read *s_read, t_history **list)
{
	(*list)->cursor = s_read->pos.col;
	set_cursor_home(s_read);
	ft_putstr_fd(tgetstr("cd", NULL), 1);
}

void	init_term(t_read *s_read, struct termios *term)
{
	struct termios	attr;
	int				ret;

	tcgetattr(0, term);
	attr = *term;
	attr.c_lflag &= ~(ECHO);
	attr.c_lflag &= ~(ISIG);
	attr.c_lflag &= ~(ICANON);
	ret = tgetent(NULL, getenv("TERM"));
	s_read->clear = tgetstr("cl", NULL);
	tcsetattr(0, TCSANOW, &attr);
}

void	get_cursor(t_read *s_read, t_history **list)
{
	char	cursor[20];
	int		ret;

	s_read->pos = (t_pos){0};
	ft_bzero(cursor, 20);
	ft_putstr_fd("\e[6n", 0);
	ret = read(0, cursor, 20);
	cursor[ret] = 0;
	ret = 2;
	s_read->pos.row = ft_atoi(cursor + ret);
	while (ft_isdigit(cursor[ret]))
		ret++;
	ret++;
	s_read->pos.col = ft_atoi(cursor + ret);
	s_read->pos.col--;
	s_read->pos.row--;
	(*list)->cursor = s_read->pos.col;
}

void	termsize(t_read *s_read)
{
	s_read->win = (t_pos){0};
	s_read->win.col = tgetnum("co");
	s_read->win.row = tgetnum("li");
	s_read->win.col--;
	s_read->win.row--;
}

t_history	*add_node(t_history **hist, t_history *node)
{
	t_history	*last;

	if (!(*hist))
	{
		(*hist) = node;
		return (*hist);
	}
	else
	{
		last = NULL;
		last = (*hist);
		while (last->next)
			last = last->next;
		node->prev = last;
		last->next = node;
		return (last->next);
	}
}
