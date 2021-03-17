/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:58:40 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/16 19:05:54 by cabouelw         ###   ########.fr       */
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

void	dollar(t_mini *mini, int i, int j, char **tmp)
{
	char	*value;

	value = ft_substr(mini->tab[i], j, checksymbol(mini->tab[i], j + 1) - j);
	value = ft_strchr(value, '$') + 1;
	*tmp = ft_strdup(ft_lstsearch(mini->myenv, value));
}

void	expansions(t_mini *mini)
{
	int		i;
	int		j;
	char	s;
	char	*tmp;
	char	*temp;

	i = 0;
	while (mini->tab[i])
	{
		j = 0;
		temp = ft_strdup("");
		while (mini->tab[i][j])
		{
			if (s == mini->tab[i][j] * -1)
				s = 0;
			if (mini->tab[i][j] < 0)
				s = mini->tab[i][j] * -1;
			if (mini->tab[i][j] == '$' && mini->tab[i][j + 1] && s != '\'')
				dollar(mini, i, j, &tmp);
			else
				tmp = ft_substr(mini->tab[i], j,\
					checksymbol(mini->tab[i], j + 1) - j);
			j = checksymbol(mini->tab[i], j + 1);
			temp = ft_strjoin(temp, tmp);
			free(tmp);
		}
		ft_strlcpy(mini->tab[i], temp, ft_strlen(temp) + 1);
		free(temp);
		i++;
	}
}

void	execution(t_mini *mini)
{
	mini->tab = NULL;
	while (mini->cmd_list && !mini->status)
	{
		while (mini->cmd_list->pipe)
		{
			check_redirec(mini);
			mini->tab = ft_strsplit(mini->cmd_list->pipe->content, " ", 1);
			expansions(mini);
			mini->tab = remove_dust(mini->tab);
			if (is_builtins(mini))
				do_builtins(mini);
			else
			{
				if (ifexist(mini))
					exec_cmd(mini);
				else
					cmd_not_found(mini);
			}
			if (mini->fd != 0)
				close(mini->fd);
			// ft_free(mini->tab);
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
