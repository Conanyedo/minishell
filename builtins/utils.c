/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:50:10 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/25 13:08:13 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap(t_mini *mini, char ***tab, int j, int l)
{
	if ((*tab)[j][l] > (*tab)[j + 1][l])
	{
		mini->temp = ft_strdup((*tab)[j]);
		free((*tab)[j]);
		(*tab)[j] = ft_strdup((*tab)[j + 1]);
		free((*tab)[j + 1]);
		(*tab)[j + 1] = ft_strdup(mini->temp);
		free(mini->temp);
	}
}

void	sortarray(t_mini *mini, char ***tab)
{
	int		i;
	int		j;
	int		l;
	int		len;

	len = 0;
	mini->temp = NULL;
	while ((*tab)[len])
		len++;
	i = -1;
	while (++i < len - 1)
	{
		j = -1;
		while (++j < len - i - 1)
		{
			l = 0;
			while ((*tab)[j][l] == (*tab)[j + 1][l])
				l++;
			swap(mini, tab, j, l);
		}
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
	if ((ft_strrchr(mini->tab[i], '/')))
		tmp[2] = ft_strdup(ft_strrchr(mini->tab[i], '/') + 1);
	else
		tmp[2] = ft_strdup(mini->tab[i]);
	list = mini->myenv;
	while (list)
	{
		if (!(ft_strncmp(list->key, tmp[0], 1)))
			edit(mini, &list, &tmp);
		list = list->next;
	}
	ft_free(tmp);
}

void	underscore(t_mini *mini)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * 4);
	tmp[0] = ft_strdup("_");
	tmp[1] = ft_strdup("=");
	tmp[3] = NULL;
	while (mini->tab[i])
		i++;
	i--;
	if (!ft_lstsearch(mini->myenv, "_"))
	{
		tmp[2] = ft_strdup("_");
		add_env(mini, tmp);
		ft_free(tmp);
		return ;
	}
	edit_underscore(mini, i);
}
