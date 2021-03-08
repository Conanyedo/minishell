/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:04:26 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/08 09:53:12 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include <stdio.h>
#include <unistd.h>

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_mini
{
	t_env	*myenv;
	char	*input;
	char	**paths;
	char	*path_value;
	int		pid;
	char	*argv[];
	
}					t_mini;

void				init_env(char **env, t_env **myenv);
char				*ft_lstsearch(t_env	*env, char *to_search);
void				prompt(t_env *env, int status);
void				parse(t_mini *mini);
int					is_builtins(t_mini *mini);
void				do_builtins(t_mini *mini);

// Builtins
void				ft_env(t_env *env);
void				ft_echo(char **str);