/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:44:28 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/18 15:21:20 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	home_end(t_read *s_read, t_history **list)
{
	int		diff;
	float	div;
	int		mod;

	diff = 0;
	if (s_read->key == K_HOME)
		return (set_cursor_home(s_read));
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

void	init_term(struct termios *term)
{
	struct termios	attr;
	char			*env;
	int				ret;

	env = getenv("TERM");
	if (!env)
		env = ft_strdup("xterm-256color");
	if (!env || g_mini->print)
		error_term("\r\033[KTERM must be set\n");
	if (tcgetattr(0, term) < 0)
		error_term("\r\033[KError in tcgetattr\n");
	attr = *term;
	attr.c_lflag &= ~(ECHO);
	attr.c_lflag &= ~(ISIG);
	attr.c_lflag &= ~(ICANON);
	ret = tgetent(NULL, env);
	if (!getenv("TERM"))
		free(env);
	if (ret == 0)
		error_term("\r\033[KCould not access to the termcap database..\n");
	if (ret < 0)
		error_term("\r\033[KTerminal type is not defined in termcap database.\n");
	if (tcsetattr(0, TCSANOW, &attr) < 0)
		error_term("\r\033[KError in tcsetattr\n");
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
