/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:04:26 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/27 12:06:38 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct		s_pipe
{
	char			*content;
	struct s_pipe	*next;
}					t_pipe;

typedef struct		s_cmd
{
	void			*content;
	struct s_pipe	*pipe;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_env
{
	char			*key;
	char			*value;
	char			*symbol;
	struct s_env	*next;
}					t_env;

typedef	struct		s_redir
{
	char			*tmpfile;
	char			*tmpstr;
	char			*file;
	char			*str;
	int				fd[2];
	int				len;
	int				err;
	int				oldinput;
	int				oldoutput;
	int				opn;
}					t_redir;

typedef struct	s_checkers
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


typedef struct		s_mini
{
	t_checkers		check;
	t_env			*myenv;
	t_cmd			*cmd;
	struct stat		stt;
	t_redir			redir;
	char			*cmd_exist;
	char			**env_array;
	char			**tab;
	char			**cmds;
	int				status;
	int				cmd_status;
	char			*input;
	char			**paths;
	char			*path_value;
	int				pid;
	int				r;
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
void				ft_free(char **arr);
int					is_builtins(t_mini *mini);
void				do_builtins(t_mini *mini);
int					checksymbol(char *tab, int i);
int					checkquotes(char *tab, int i, char *q);
void				trimming(t_mini *mini);
void				dollar(t_mini *mini, t_pipe *pipe, int i, char **tmp);
void				tilde(t_mini *mini);
void				expansions(t_mini *mini, t_pipe *pipe);
int					ifexist(t_mini *mini);
void				if_isdirect(t_mini *mini, char *s);
void				not_exist(t_mini *mini);
void				commands(t_mini *mini);

//linkedlist
void				init_env(char **env, t_env **myenv);
char				*ft_lstsearch(t_env	*env, char *key);
void				ft_lsttoarray(t_env *env, char ***tab);
int					ft_listsize(t_env *env);



// parssing
void				parse(t_mini *mini);
void				ft_error_end(char *s, t_mini *mini);
void				ft_check_err(t_mini	*mini);
void				check_point(t_mini *mini, int i);
void				exec_cmd(t_mini *mini);
void				check_bdl_quot(t_mini *mini, int i);
void				check_one_quot(t_mini *mini, int i);
void				check_symbols(t_mini *mini, int i);
void				error_newline(t_mini *mini, int i);
void				error_symbols(t_mini *mini, int nb);
void				check_pipes(t_mini *mini, int i);
void				error_pips(t_mini *mini, int res);
char				check_slash(t_mini *mini, int i);
void				check_all(t_mini *mini, int i, int idx);
void				redir(t_mini *mini, t_pipe **pipe, int i);
int					redir_right(t_mini *mini, int i);
int					redir_left(t_mini *mini, int i);
int					check_redir(char *str);
char				**remove_dust(char **str);

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
void				edit_env(t_mini *mini, char **splitted);
void				edit(t_mini *mini, t_env **list, char ***splitted);
void				print_export(t_mini *mini);
void				sortarray(t_mini *mini, char ***tab);
void				underscore(t_mini *mini);


//errors cmd
void				cmd_not_found(t_mini *mini);
void				error_file(t_mini *mini, char *file, char *cmd);
void				error_env(t_mini *mini, char *env, char *cmd);
void				is_directory(t_mini *mini);
void				permission(t_mini *mini);
void				error_arg(t_mini *mini);
