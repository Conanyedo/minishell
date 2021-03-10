/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:55:23 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/10 10:50:45 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse(t_mini *mini)
{
	int		i;
	int		j;
	int		c;
	char	**tmp;

	i = 0;
	j = 0;
	c = 0;
	tmp = NULL;
	mini->input = ft_strtrim(mini->input, " \t");
	ft_separate(mini);
    if (ft_strchr(mini->input,'<') || ft_strchr(mini->input,'>'))
        check_symbols(mini);
	mini->cmds = ft_strsplit(mini->input, ";", 1);
	while (mini->cmds[c])
	{
		printf("cmd : %s\n", mini->cmds[c]);
		c++;
	}
	printf("----------\n");
	mini->cmd_list = (t_list**)malloc(sizeof(t_list*) * (c + 1));
	while (mini->cmds[i])
	{
		mini->cmds[i] = ft_strtrim(mini->cmds[i], " \t");
		tmp = ft_strsplit(mini->cmds[i], "|", 1);
		printf("++++++++++++++\n");
		j = 0;
		while (tmp[j])
		{
			tmp[j] = ft_strtrim(tmp[j], " \t");
			// printf("\n---------------\n");
			mini->cmd_list[j] = (t_list*)malloc(sizeof(t_list) * (ft_strlen(tmp[j]) + 1));
			mini->cmd_list[j]->content = tmp[j];
			if (tmp[j + 1])
				mini->cmd_list[j]->next = *mini->cmd_list;
			printf("{%s}\n", mini->cmd_list[j]->content);
			j++;
		}
		mini->cmd_list[i]->next = NULL;
		ft_free(tmp);
		// printf("------\n(|%s|)\n", mini->cmds[i]);
		i++;
	}
	// mini->path_value = ft_lstsearch(mini->myenv, "PATH");
	// mini->paths = ft_split(mini->path_value, ':');
}
