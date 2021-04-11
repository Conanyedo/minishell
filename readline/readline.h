/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:51:13 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/06 12:20:20 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "Libft/libft.h"
#include <termios.h>
#include <termcap.h>
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>
#include <math.h>

# define key_u 0x415B1B
# define key_dw 0x425B1B
# define key_r 0x435B1B
# define key_l 0x445B1B
# define key_del 0x7E335B1B
# define key_esc 0x1B
# define key_ctrl_l 0x485b1b
// # define key_space 0x20
// # define key_enter 0xA
// # define key_backspace 0x7F

typedef struct		s_pos
{
	int				col;
	int				row;
}					t_pos;

typedef struct		s_char
{
	int				c;
	struct s_char	*prev;
	struct s_char	*next;
}					t_char;

typedef struct		s_history
{
	// char				*content;
	int					len;
	struct s_char		*str;
	struct s_history	*prev;
	struct s_history	*next;
}					t_history;

typedef struct		s_read
{
	struct termios	term;
	t_history		*hist;
	t_pos			pos;
	t_pos			win;
	t_char			*chars;
	char			*input;
	int				key;
	int				len;
	int				cursor;
	int				fd;
	int				up;
	char			*tmp;
	int				old;
	char			*clear;
}					t_read;

void	readline(t_read *s_read, struct termios *term, t_history **hist);
void	addchar(t_history **list, int c);
void	add_char(t_read *s_read, t_history **list, int c);
void	delchar(t_history **list);
void	delete_char(t_read *s_read, t_history **list);
void	up(t_read *s_read, t_history **list);
void	down(t_read *s_read, t_history **list);
void	fill_input(t_read *s_read, t_history **list, t_history **hist);
void	get_cursor(t_read *s_read);
void	termsize(t_read *s_read);
void	init_term(t_read *s_read, struct termios *term);
void	set_cursor_home(t_read *s_read);

//history
t_history	*add_node(t_history **hist, t_history *node);
void		create_node(t_history **node);
void		create_chars(t_history **node, char *line);
void		fill_hist(t_history **hist);
void		fill_file(t_history **hist, int fd);
void		history(t_read *s_read, t_history **hist);
