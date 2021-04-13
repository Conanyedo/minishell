/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:50:10 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/13 12:27:14 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sortlinkedlist(t_env **sorted, t_env *list)
{
	t_env	*current;

	if (*sorted == NULL)
	{
		list->next = *sorted;
		*sorted = list;
		return ;
	}
	if (ft_strcmp((*sorted)->key, list->key) >= 0)
	{
		list->next = *sorted;
		*sorted = list;
	}
	else
	{
		current = *sorted;
		while (current->next && ft_strcmp(current->next->key, list->key) < 0)
			current = current->next;
		list->next = current->next;
		current->next = list;
	}
}

void	dup_list(t_mini *mini, t_env **dup)
{
	t_env	*list;
	t_env	*current;

	list = NULL;
	current = NULL;
	*dup = NULL;
	list = mini->myenv;
	(*dup) = (t_env *)malloc(sizeof(t_env));
	(*dup)->next = NULL;
	current = *dup;
	while (list)
	{
		current->key = list->key;
		current->symbol = list->symbol;
		current->value = list->value;
		current->print = list->print;
		list = list->next;
		if (!list)
			break ;
		current->next = (t_env *)malloc(sizeof(t_env));
		current = current->next;
	}
	current->next = NULL;
}

void	insertionsort(t_mini *mini, t_env **sorted)
{
	t_env	*list;
	t_env	*current;

	list = NULL;
	(*sorted) = NULL;
	dup_list(mini, &current);
	while (current)
	{
		list = current->next;
		sortlinkedlist(sorted, current);
		current = list;
	}
}

void	edit_underscore(t_mini *mini, int i)
{
	char	**tmp;
	t_env	*list;

	list = NULL;
	tmp = (char **)malloc(sizeof(char *) * 4);
	tmp[0] = ft_strdup("_");
	tmp[1] = ft_strdup("=");
	tmp[3] = NULL;
	if ((ft_strrchr(mini->tabu[i], '/')))
		tmp[2] = ft_strdup(ft_strrchr(mini->tabu[i], '/') + 1);
	else
		tmp[2] = ft_strdup(mini->tabu[i]);
	list = mini->myenv;
	while (list)
	{
		if (!(ft_strncmp(list->key, tmp[0], 1)))
			edit(mini, &list, &tmp, 0);
		list = list->next;
	}
	ft_free(&tmp);
}

void	underscore(t_mini *mini)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	if (!mini->tabu[i])
		return ;
	tmp = (char **)malloc(sizeof(char *) * 4);
	tmp[0] = ft_strdup("_");
	tmp[1] = ft_strdup("=");
	tmp[2] = ft_strdup("_");
	tmp[3] = NULL;
	while (mini->tabu[i])
		i++;
	i--;
	if (!ft_lstsearch(mini->myenv, "_", &mini->print))
	{
		add_env(mini, tmp);
		ft_free(&tmp);
		return ;
	}
	ft_free(&tmp);
	edit_underscore(mini, i);
}
