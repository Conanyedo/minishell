/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:58:40 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/13 14:40:24 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ifexist(t_mini *mini)
{
	int		i;
	int		fd;
	char	*cmd;
	char	*joincmd;

	i = 0;
	cmd = mini->tab[0];
	while (mini->paths[i])
	{
		joincmd = ft_strjoin("/",cmd);
		joincmd = ft_strjoin(mini->paths[i],joincmd);
		if ((fd = open(joincmd,O_RDONLY)) > 0)
		{
			mini->cmd_exist = joincmd;
			close(fd);
			return (1);
		}
		free(joincmd);
		i++;
	}
	return (0);
}

void	execution(t_mini *mini, char **env)
{
	// t_cmd	*list;
	// t_pipe	*pipelist;
	
	// list = NULL;
	// pipelist = NULL;
	// list = mini->cmd_list;
	while (!mini->status && mini->cmd_list)
	{
		mini->tab = ft_strsplit(mini->cmd_list->pipe->content, " ", 1);
		if (is_builtins(mini))
			do_builtins(mini);
		else
		{
			if (ifexist(mini))
				exec_cmd(mini, env);
			else
				cmd_not_found(mini);
		}
			
		mini->cmd_list = mini->cmd_list->next;
	}
}

int		main(int ac, char **av, char **env)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	mini.myenv = (t_env *){0};
	mini.check = (t_checkers){0};
	mini.cmd_list = (t_cmd*){0};
	mini = (t_mini){0};
	init_env(env, &mini.myenv);
	while(1)
	{
		prompt(&mini);
		get_next_line(0, &mini.input);
		parse(&mini);
		execution(&mini, env);
		free(mini.input);
		mini.input = NULL;
	}
}