/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:04:26 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/15 16:24:10 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "Libft/libft.h"
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include <termcap.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <math.h>

# define KU 0x415B1B
// # define KU2 0x414F1B
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

typedef struct s_char
{
	int				c;
	struct s_char	*prev;
	struct s_char	*next;
}					t_char;

typedef struct s_history
{
	int					len;
	int					cursor;
	int					rank;
	struct s_char		*str;
	struct s_char		*tmp;
	struct s_history	*prev;
	struct s_history	*next;
}						t_history;

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

typedef struct s_pipe
{
	char			*content;
	struct s_pipe	*next;
}					t_pipe;

typedef struct s_cmd
{
	void			*content;
	struct s_pipe	*pipe;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*symbol;
	int				print;
	struct s_env	*next;
}					t_env;

typedef struct s_redir
{
	char			*tmpfile;
	char			*tmpstr;
	char			*file;
	char			*str;
	int				fd[2];
	int				len;
	int				err;
	int				opn;
}					t_redir;

typedef struct s_checkers
{
	int			point;
	int			pipe;
	int			and;
	int			quota;
	int			dbl_quota;
	int			end;
	int			error;
	char		symbols;
	int			left;
	int			right;
	char		quote;
	char		*tmp;
	char		*value;
}				t_checkers;

typedef struct s_mini
{
	t_checkers		check;
	t_env			*myenv;
	t_cmd			*cmd;
	t_history		*hist;
	struct stat		stt;
	t_redir			redir;
	char			**pwd;
	char			**oldpwd;
	char			*prompt;
	char			*home;
	int				pipe[2];
	int				err_pipe[2];
	int				p;
	char			*cl;
	char			*color;
	char			*cm;
	char			*sc;
	int				oldinput;
	int				oldoutput;
	int				ret;
	char			*cmd_exist;
	char			**env_array;
	char			**tabu;
	char			**cmds;
	int				status;
	int				cmd_status;
	char			*input;
	char			**paths;
	char			*path_value;
	int				pid;
	int				r;
	int				print;
	int				plus;
	int				fd[2];
	int				fdtst;
	char			*tmp;
	char			*temp;
	char			buff[1028];
}					t_mini;

t_mini	*g_mini;

void				prompt(t_mini *mini);
void				execution(t_mini *mini);
void				ft_free(char ***arr);
int					is_builtins(t_mini *mini);
void				do_builtins(t_mini *mini);
int					checksymbol(char *tabu, int i);
int					checkquotes(char *tabu, int i, char *q);
void				trimming(t_mini *mini);
void				dollar(t_mini *mini, char *tabu, int i, char **tmp);
void				tilde(t_mini *mini);
void				expansions(t_mini *mini, t_pipe *pipe, int i, int s);
int					ifexist(t_mini *mini, int i);
void				if_isdirect(t_mini *mini, char *s);
void				not_exist(t_mini *mini);
void				commands(t_mini *mini, t_pipe *pip);

//linkedlist
void				init_env(char **env, t_env **myenv);
char				*ft_lstsearch(t_env	*env, char *key, int *print);
void				ft_lsttoarray(t_env *env, char ***tabu);
int					ft_listsize(t_env *env);
void				sortlinkedlist(t_env **sorted, t_env *list);
void				dup_list(t_mini *mini, t_env **dup);
void				insertionsort(t_mini *mini, t_env **sorted);

// parssing
void				parse(t_mini *mini);
void				check_point(t_mini *mini, int i);
void				exec_cmd(t_mini *mini);
void				check_bdl_quot(t_mini *mini, int i);
void				check_one_quot(t_mini *mini, int i);
void				check_symbols(t_mini *mini, int i);
void				error_symbols(t_mini *mini, int nb);
void				check_pipes(t_mini *mini, int i);
char				check_slash(t_mini *mini, int i);
void				check_all(t_mini *mini, int i, int idx);
void				redir(t_mini *mini, t_pipe **pipe, int i);
int					redir_right(t_mini *mini, int i, char t);
int					redir_left(t_mini *mini, int i, char t);
int					check_redir(char *str);
int					cutfilename(t_mini *mini, int i, char t, char **file);
char				**remove_dust(char ***str);

// Builtins
void				do_builtins(t_mini *mini);
int					is_builtins(t_mini *mini);
void				ft_env(t_mini *mini);
void				ft_echo(t_mini *mini);
void				ft_exit(t_mini *mini);
void				ft_cd(t_mini *mini);
void				ft_export(t_mini *mini);
void				ft_pwd(t_mini *mini);
void				ft_unset(t_mini *mini);
void				add_env(t_mini *mini, char **splitted);
void				edit_env(t_mini *mini, char **splitted, int print);
void				edit(t_mini *mini, t_env **list, char ***splitted,
						int print);
void				print_export(t_mini *mini);
void				sortarray(t_mini *mini, char ***tabu);
void				underscore(t_mini *mini);
void				pipe_handler(t_mini *mini, t_pipe *pip);
int					isredirect_loop(t_mini *mini, char *s, int i);
void				close_fd(t_mini *mini);
void				ft_dup(t_mini *mini);
void				exec_cmdplus(t_mini *mini);

//errors cmd
void				cmd_not_found(t_mini *mini);
void				error_file(t_mini *mini, char *file, char *cmd);
void				error_env(t_mini *mini, char *env, char *cmd);
void				is_directory(t_mini *mini, char *file);
void				permission(t_mini *mini, char *file);
void				error_arg(t_mini *mini);
void				ambiguous(t_mini *mini, char *file);

//readline
char				*readline(t_mini *mini, t_history **hist,
						struct termios *term);
void				keys(t_mini *mini, t_read *s_read, t_history **hist);
void				add_char(t_read *s_read, t_history **list, int c);
void				delchar(t_history **list);
void				delete_char(t_read *s_read, t_history **list);
void				delete_node(t_history **hist);
void				free_str(t_char	**node);
void				up(t_read *s_read, t_history **list);
void				down(t_read *s_read, t_history **list);
void				left(t_read *s_read, t_history **list);
void				right(t_read *s_read, t_history **list);
void				fill_input(t_read *s_read, t_history **list,
						t_history **hist);
void				get_cursor(t_read *s_read, t_history **list);
void				termsize(t_read *s_read);
void				init_term(t_read *s_read, struct termios *term);
void				cursor_home_clean(t_read *s_read, t_history **list);
void				set_cursor_home(t_read *s_read);
void				home_end(t_read *s_read, t_history **list);
void				clear_term(t_mini *mini, t_read *s_read, t_history **list);
void				printing(t_read *s_read, t_history **list, int c);
void				dup_str(t_char *node, t_char **dup);

//signals
void				ctrl_c(t_mini *mini, t_read *s_read, t_history **list);
void				ctrl_d(t_history **list);
void				handle_sigint(int sig);
void				handle_sigquit(int sig);

//history
t_history			*add_node(t_history **hist, t_history *node);
void				create_node(t_history **node, int rank);
void				create_chars(t_history *node, t_char **str, char *line);
void				fill_hist(t_history **hist);
void				fill_file(t_history **hist, int fd);
void				history(t_read *s_read, t_history **hist);

#endif