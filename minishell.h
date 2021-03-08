/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:04:26 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/08 11:51:57 by ybouddou         ###   ########.fr       */
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
	char		error;
}				t_checkers;

typedef struct		s_mini
{
	t_checkers		check;
	t_env			*myenv;
	char			*input;
	char			**paths;
	char			*path_value;
	int				pid;
	char			*argv[];
}					t_mini;

void				init_env(char **env, t_env **myenv);
char				*ft_lstsearch(t_env	*env, char *to_search);
void				prompt(t_env *env, int status);
void				parse(t_mini *mini);
int					is_builtins(t_mini *mini);
void				do_builtins(t_mini *mini);
void				check_point(t_mini *mini);
void				ft_error_end(char *s, char c);
void				ft_check_err(t_mini	*mini);
void				ft_check_point(t_mini *mini);
void				exec_cmd(t_mini *mini, char **env);

// Builtins
void				ft_env(t_env *env);
void				ft_echo(char **str);