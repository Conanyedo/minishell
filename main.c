/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:58:40 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/22 15:49:35 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ifexist(t_mini *mini)
{
	int		i;
	int		fd;
	char	*slashcmd;

	i = 0;
	mini->path_value = ft_lstsearch(mini->myenv, "PATH");
	mini->paths = (mini->path_value) ? ft_split(mini->path_value, ':') : NULL;
	slashcmd = ft_strjoin("/", mini->tab[0]);
	while (mini->paths[i])
	{
		mini->cmd_exist = ft_strjoin(mini->paths[i], slashcmd);
		if ((fd = open(mini->cmd_exist, O_RDONLY)) > 0)
		{
			ft_strlcpy(mini->tab[0], mini->cmd_exist,\
				ft_strlen(mini->cmd_exist) + 1);
			close(fd);
			free(slashcmd);
			return (1);
		}
		free(mini->cmd_exist);
		i++;
	}
	free(slashcmd);
	return (0);
}

void	execution(t_mini *mini)
{
	mini->tab = NULL;
	while (mini->cmd)
	{
		while (mini->cmd->pipe)
		{
			expansions(mini);
			redir(mini, 0);
			mini->tab = ft_strsplit(mini->cmd->pipe->content, " ", 1);
			mini->tab = remove_dust(mini->tab);
			if (is_builtins(mini) && mini->redir.len != -1)
				do_builtins(mini);
			else if (mini->redir.len != -1)
				exec_cmd(mini);
			if (mini->fd[0] > 1)
				close(mini->fd[0]);
			ft_free(mini->tab);
			mini->tab = NULL;
			mini->cmd->pipe = mini->cmd->pipe->next;
		}
		mini->cmd = mini->cmd->next;
	}
}

int		main(int ac, char **av, char **env)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	mini.myenv = (t_env *){0};
	mini.check = (t_checkers){0};
	mini.cmd = (t_cmd*){0};
	mini = (t_mini){0};
	init_env(env, &mini.myenv);
	while (1)
	{
		prompt(&mini);
		get_next_line(0, &mini.input);
		parse(&mini);
		if (!mini.status)
			execution(&mini);
		free(mini.input);
		mini.input = NULL;
	}
}
