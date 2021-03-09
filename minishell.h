/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:04:26 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/09 14:43:21 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct	s_checkers
{
	int			point;
	int			pipe;
	int			and;
	int			end;
	int			error;
	char		*err;
	char		*value;
}				t_checkers;

typedef struct		s_mini
{
	t_checkers		check;
	t_env			*myenv;
	t_list			*pip_list;
	char			**cmd;
	int				status;
	char			*input;
	char			**paths;
	char			*path_value;
	int				pid;
	char			*argv[];
}					t_mini;

void				init_env(char **env, t_env **myenv);
char				*ft_lstsearch(t_env	*env, char *to_search);
void				prompt(t_mini *mini);
int					is_builtins(t_mini *mini);
void				do_builtins(t_mini *mini);
void				check_point(t_mini *mini);

// parssing
void				parse(t_mini *mini);
void				ft_error_end(char *s, t_mini *mini);
void				ft_check_err(t_mini	*mini);
void				ft_separate(t_mini *mini);
void				exec_cmd(t_mini *mini, char **env);
int					check_bdl_quot(t_mini *mini, int i);
int					check_one_quot(t_mini *mini, int i);
void				check_symbols(t_mini *mini);
void				error_newline(t_mini *mini);

// Builtins
void				ft_env(t_env *env);
void				ft_echo(char **str);
void				ft_exit(t_mini *mini);
void				ft_cd(t_mini *mini);
void				ft_export(t_mini *mini);
void				ft_pwd(t_mini *mini);
void				ft_unset(t_mini *mini);