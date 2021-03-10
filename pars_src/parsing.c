/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:55:23 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/09 15:04:58 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse(t_mini *mini)
{
    int i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	mini->input = ft_strtrim(mini->input, " \t");
	ft_separate(mini);
    if (ft_strchr(mini->input,'<') || ft_strchr(mini->input,'>'))
        check_symbols(mini);
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
		i++;
	}
	// printf("\n---------------\n");
	// while (mini->pip_list)
	// {
	// 	printf("{%s}\n", mini->pip_list->content);
	// 	mini->pip_list = mini->pip_list->next;
	// }
	// mini->path_value = ft_lstsearch(mini->myenv, "PATH");
	// mini->paths = ft_split(mini->path_value, ':');
}
