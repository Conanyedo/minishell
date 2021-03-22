/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:02:23 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/22 17:16:54 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env(t_mini *mini, char **splitted)
{
	t_env	*list;

	list = NULL;
	list = mini->myenv;
	while (list->next)
		list = list->next;
	list->next = (t_env*)malloc(sizeof(t_env));
	list = list->next;
	list->key = ft_strdup(splitted[0]);
	list->symbol = ft_strdup(splitted[1]);
	list->value = ft_strdup(splitted[2]);
	list->next = NULL;
}

void	edit(t_mini *mini, t_env **list, char ***splitted)
{
	char	*tmp;

	tmp = ft_strdup("");
	if (*(*list)->symbol == '=')
		ft_strlcpy((*list)->symbol, "=", 2);
	else
		ft_strlcpy((*list)->symbol, (*splitted)[1], 2);
	if (*(*splitted)[1])
	{
		if (mini->plus == 1)
			free((*list)->value);
		else if (mini->plus == 2)
		{
			tmp = ft_strjoin((*list)->value, (*splitted)[2]);
			free((*list)->value);
			free((*splitted)[2]);
			(*splitted)[2] = ft_strdup(tmp);
		}
		(*list)->value = ft_strdup((*splitted)[2]);
	}
	free(tmp);
	
}

void	edit_env(t_mini *mini, char **splitted)
{
	t_env	*list;
	char	*tmp;

	list = NULL;
	if (!ft_strncmp("_", splitted[0], ft_strlen(splitted[0])))
		return ;
	tmp = ft_strdup("");
	list = mini->myenv;
	while (list)
	{
		if (!(ft_strncmp(list->key, splitted[0], ft_strlen(splitted[0]))))
			edit(mini, &list, &splitted);
		list = list->next;
	}
}
