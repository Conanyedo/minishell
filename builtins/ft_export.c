/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:03:14 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/14 17:01:14 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**export_errors(t_mini *mini, char ***tmp, char *tab)
{
	ft_putstr_fd("export: `", 1);
	ft_putstr_fd(tab, 1);
	ft_putstr_fd("\': not a valid identifier\n", 1);
	mini->status = 1;
	ft_free(*tmp);
	(*tmp) = NULL;
	return (NULL);
}

char	**filling(t_mini *mini, char ***tmp, char *tab, int i)
{
	if (tab[0] == '=')
		return (export_errors(mini, tmp, tab));
	else
	{
		(*tmp)[0] = ft_strdup(ft_substr(tab, 0, i));
		(*tmp)[1] = ft_strdup("=");
		(*tmp)[2] = ft_strdup(tab + i + 1);
		(*tmp)[3] = NULL;
	}
	return (*tmp);
}

char	**split_env(t_mini *mini, char *tab)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	tmp = (char **)malloc(sizeof(char *) * 4);
	while (tab[i] && tab[i] != '=')
	{
		if (ft_isalnum(tab[i]) || tab[i] == '_')
			i++;
		else
			return (export_errors(mini, &tmp, tab));
	}
	if (!tab[i])
	{
		tmp[0] = ft_strdup(tab);
		tmp[1] = ft_strdup("");
		tmp[2] = ft_strdup("");
		tmp[3] = NULL;
		return (tmp);
	}
	return (filling(mini, &tmp, tab, i));
}

void	print_export(t_mini *mini)
{
	t_env	*list;

	list = mini->myenv;
	while (list)
	{
		if (ft_strncmp(list->key, "_", ft_strlen(list->key)))
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(list->key, 1);
			if (*list->symbol)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(list->value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
		list = list->next;
	}
	return ;
}

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

void	edit_env(t_mini *mini, char **splitted)
{
	t_env	*list;

	list = NULL;
	if (!ft_strncmp("_", splitted[0], ft_strlen(splitted[0])))
		return ;
	list = mini->myenv;
	while (list)
	{
		if (!(ft_strncmp(list->key, splitted[0], ft_strlen(splitted[0]))))
		{
			if (*list->symbol == '=')
				ft_strlcpy(list->symbol, "=", 2);
			else
				ft_strlcpy(list->symbol, splitted[1], 2);
			if (*splitted[1])
			{
				free(list->value);
				list->value = ft_strdup(splitted[2]);
			}
		}
		list = list->next;
	}
}

void	ft_export(t_mini *mini)
{
	int		i;
	char	**splitted;

	i = 1;
	splitted = NULL;
	if (!mini->tab[i])
		return (print_export(mini));
	while (mini->tab[i])
	{
		splitted = split_env(mini, mini->tab[i]);
		if (!splitted)
			return ;
		if (ft_lstsearch(mini->myenv, splitted[0]))
			edit_env(mini, splitted);
		else
			add_env(mini, splitted);
		ft_free(splitted);
		i++;
	}
}