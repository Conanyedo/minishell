/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:03:21 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/12 13:13:24 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	if_nothead(t_mini *mini, t_env **list, int i)
{
	t_env	*prev;

	prev = NULL;
	while (*list && ft_strncmp(mini->tabu[i], (*list)->key, \
		ft_strlen(mini->tabu[i])))
	{
		prev = *list;
		*list = (*list)->next;
	}
	if (*list)
	{
		free((*list)->key);
		free((*list)->value);
		free((*list)->symbol);
		prev->next = (*list)->next;
	}
}

void	ft_unset(t_mini *mini)
{
	t_env	*list;
	int		i;

	i = 1;
	while (mini->tabu[i])
	{
		list = NULL;
		list = mini->myenv;
		while (list)
		{
			if (!(ft_strncmp(list->key, mini->tabu[i], \
				ft_strlen(mini->tabu[i]))))
				list->print = 1;
			list = list->next;
		}
		i++;
	}
	mini->cmd_status = 0;
}
