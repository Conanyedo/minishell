/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:51:13 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/10 11:42:47 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H
#include "../minishell.h"
# include "../Libft/libft.h"
# include <termios.h>
# include <termcap.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <math.h>

# define KU 0x415B1B
# define KDW 0x425B1B
# define KR 0x435B1B
# define KL 0x445B1B
# define K_END 0x465b1b
# define K_HOME 0x485b1b
# define KDEL 0x7E335B1B
# define KESC 0x1B
# define KCL 0x485b1b

typedef struct s_pos
{
	int				col;
	int				row;
}					t_pos;

// typedef struct s_char
// {
// 	int				c;
// 	struct s_char	*prev;
// 	struct s_char	*next;
// }					t_char;

// typedef struct s_history
// {
// 	int					len;
// 	int					cursor;
// 	struct s_char		*str;
// 	struct s_history	*prev;
// 	struct s_history	*next;
// }						t_history;

typedef struct s_read
{
	t_pos			pos;
	t_pos			win;
	char			*prompt;
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

char		*readline(t_mini *mini, t_history **hist);
void		keys(t_mini *mini, t_read *s_read, t_history **hist);
void		addchar(t_history **list, int c);
void		add_char(t_read *s_read, t_history **list, int c);
void		delchar(t_history **list);
void		delete_char(t_read *s_read, t_history **list);
void		up(t_read *s_read, t_history **list);
void		down(t_read *s_read, t_history **list);
void		left(t_read *s_read, t_history **list);
void		right(t_read *s_read, t_history **list);
void		fill_input(t_read *s_read, t_history **list, t_history **hist);
void		get_cursor(t_read *s_read, t_history **list);
void		termsize(t_read *s_read);
void		init_term(t_read *s_read, struct termios *term);
void		cursor_home_clean(t_read *s_read, t_history **list);
void		set_cursor_home(t_read *s_read);
void		set_cursor_end(t_read *s_read, t_history **list);
void		clear_term(t_mini *mini, t_read *s_read, t_history **list);
void		printing(t_read *s_read, t_history **list, int c);

//signals
void		handle_sigint(t_read *s_read);

//history
t_history	*add_node(t_history **hist, t_history *node);
void		create_node(t_history **node);
void		create_chars(t_history **node, char *line);
void		fill_hist(t_history **hist);
void		fill_file(t_history **hist, int fd);
void		history(t_read *s_read, t_history **hist);
#endif