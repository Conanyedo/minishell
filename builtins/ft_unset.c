/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:03:21 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/19 17:43:48 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	if_nothead(t_mini *mini, t_env **list, int i)
{
	t_env	*prev;

	prev = NULL;
	while (*list && ft_strncmp(mini->tab[i], (*list)->key,
		ft_strlen(mini->tab[i])))
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
	while (mini->tab[i])
	{
		list = NULL;
		list = mini->myenv;
		if (list && !ft_strncmp(mini->tab[i], list->key,
			ft_strlen(mini->tab[i])))
		{
			free(list->key);
			free(list->symbol);
			free(list->value);
			mini->myenv = list->next;
		}
		else
			if_nothead(mini, &list, i);
		i++;
	}
	mini->cmd_status = 0;
}
