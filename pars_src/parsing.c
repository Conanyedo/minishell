/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:55:23 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/11 11:49:50 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	splitting(t_mini *mini)
{
	int		i;
	int		j;
	char	**splitted;
	t_cmd	*list;
	t_pipe	*pipelist;

	i = 0;
	splitted = NULL;
	list = NULL;
	pipelist = NULL;
	mini->cmd_list = NULL;
	mini->cmd_list = (t_cmd*)malloc(sizeof(t_cmd));
	mini->cmd_list->next = NULL;
	mini->cmd_list->pipe = NULL;
	list = mini->cmd_list;
	while (mini->cmds[i])
	{
		list->content = ft_strtrim(mini->cmds[i], " \t");
		splitted = ft_strsplit(list->content, "|", 1);
		list->pipe = NULL;
		list->pipe = (t_pipe*)malloc(sizeof(t_pipe));
		list->pipe->next = NULL;
		pipelist = list->pipe;
		j = 0;
		while (splitted[j])
		{
			pipelist->content = ft_strtrim(splitted[j], " \t");
			if (!splitted[j + 1])
				break ;
			pipelist->next = (t_pipe*)malloc(sizeof(t_pipe));
			pipelist = pipelist->next;
			j++;
		}
		pipelist->next = NULL;
		ft_free(splitted);
		if (!mini->cmds[i + 1])
			break ;
		list->next = (t_cmd*)malloc(sizeof(t_cmd));
		list = list->next;
		i++;
	}
	list->next = NULL;
}

void	parse(t_mini *mini)
{
	mini->input = ft_strtrim(mini->input, " \t");
	ft_checkpoints(mini);
	check_symbols(mini);
	check_pipes(mini);
	if (mini->status)
		return;
	mini->cmds = ft_strsplit(mini->input, ";", 1);
	splitting(mini);
	
	// t_cmd	*list;
	// t_pipe	*pipelist;
	// list = NULL;
	// pipelist = NULL;
	// list = mini->cmd_list;
	// while (list)
	// {
	// 	printf("|%s|\n", list->content);
	// 	pipelist = list->pipe;
	// 	while (pipelist)
	// 	{
	// 		printf("{%s}\n", pipelist->content);
	// 		pipelist = pipelist->next;
	// 	}
	// 	list = list->next;
	// }
	// mini->path_value = ft_lstsearch(mini->myenv, "PATH");
	// mini->paths = ft_split(mini->path_value, ':');
}