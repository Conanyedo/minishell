/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:58:40 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/17 14:33:54 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ifexist(t_mini *mini)
{
	int		i;
	int		fd;
	char	*slashcmd;

	i = 0;
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
	while (mini->cmd_list && !mini->status)
	{
		while (mini->cmd_list->pipe)
		{
			mini->tab = ft_strsplit(mini->cmd_list->pipe->content, " ", 1);
			// printf("++++\n");
			// expansions(mini);
			// trimming(mini);
			if (is_builtins(mini))
				do_builtins(mini);
			else
				exec_cmd(mini);
			ft_free(mini->tab);
			mini->tab = NULL;
			mini->cmd_list->pipe = mini->cmd_list->pipe->next;
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
