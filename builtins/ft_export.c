/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:03:14 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/12 15:49:31 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**export_errors(t_mini *mini, char **tmp)
{
	if (!*tmp[0])
	{
		ft_putstr_fd("export: `=", 1);
		ft_putstr_fd(tmp[1], 1);
		ft_putstr_fd("\': not a valid identifier\n", 1);
		ft_free(tmp);
		mini->status = 1;
		return (NULL);
	}
	return (tmp);
}

char	**split_env(t_mini *mini, char *tab)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	tmp = (char **)malloc(sizeof(char *) * 3);
	while (tab[i] && tab[i] != '=')
	{
		if (ft_isalnum(tab[i]) || tab[i] == '_')
			i++;
		else
		{
			ft_putstr_fd("export: `", 1);
			ft_putstr_fd(tab, 1);
			ft_putstr_fd("\': not a valid identifier\n", 1);
			mini->status = 1;
			return (NULL);
		}
	}
	if (!tab[i])
	{
		tmp[0] = ft_strdup(tab);
		tmp[1] = NULL;
		tmp[2] = NULL;
	}
	else
	{
		tmp[0] = ft_strdup(ft_substr(tab, 0, i));
		tmp[1] = ft_strdup(tab + i + 1);
		tmp[2] = NULL;
		tmp = export_errors(mini, tmp);
	}
	return (tmp);
}

void	print_export(t_mini *mini)
{
	t_env	*fresh;

	fresh = mini->myenv;
	while (fresh)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(fresh->key, 1);
		if (!*fresh->value)
			return (ft_putstr_fd("\n", 1));
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(fresh->value, 1);
		ft_putstr_fd("\"\n", 1);
		fresh = fresh->next;
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
	if (splitted[1])
		list->value = ft_strdup(splitted[1]);
	else
		list->value = ft_strdup("");
	list->next = NULL;
}

void	edit_env(t_mini *mini, char **splitted)
{
	t_env	*list;

	list = NULL;
	list = mini->myenv;
	while (list)
	{
		if (!(ft_strncmp(list->key, splitted[0], ft_strlen(splitted[0]))))
			list->value = ft_strdup(splitted[1]);
		list = list->next;
	}
	print_export(mini);
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