/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:55:23 by cabouelw          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/03/10 10:50:45 by ybouddou         ###   ########.fr       */
=======
/*   Updated: 2021/03/09 15:04:58 by cabouelw         ###   ########.fr       */
>>>>>>> 54c10775de143488745de78850d1290c00d52aef
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse(t_mini *mini)
{
<<<<<<< HEAD
	int		i;
=======
    int i;
>>>>>>> 54c10775de143488745de78850d1290c00d52aef
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
<<<<<<< HEAD
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
=======
	mini->cmd = ft_split(mini->input, ';');
	while (mini->cmd[i])
	{
		// mini->cmd[i] = ft_strtrim(mini->cmd[i], " \t");
		// tmp = ft_split(mini->cmd[i], '|');
		// j = 0;
		// while (tmp[j])
		// {
		// 	printf("\n---------------\n");
		// 	mini->pip_list->content = tmp[j];
		// 	if (tmp[j + 1])
		// 		mini->pip_list->next = mini->pip_list;
		// 	printf("{%s}\n", mini->pip_list->content);
		// 	j++;
		// }
		// mini->pip_list->next = NULL;
		// printf("------\n(|%s|)\n", mini->cmd[i]);
>>>>>>> 54c10775de143488745de78850d1290c00d52aef
		i++;
	}
	// mini->path_value = ft_lstsearch(mini->myenv, "PATH");
	// mini->paths = ft_split(mini->path_value, ':');
}
