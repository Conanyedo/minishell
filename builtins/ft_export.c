/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:03:14 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/22 17:02:39 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**export_errors(t_mini *mini, char ***tmp, char *tab)
{
	(*tmp)[0] = NULL;
	(*tmp)[1] = NULL;
	(*tmp)[2] = NULL;
	(*tmp)[3] = NULL;
	ft_putstr_fd("export: `", 1);
	ft_putstr_fd(tab, 1);
	ft_putstr_fd("\': not a valid identifier\n", 1);
	mini->cmd_status = 1;
	if (*tmp)
		ft_free(*tmp);
	(*tmp) = NULL;
	return (NULL);
}

char	**filling(t_mini *mini, char ***tmp, char *tab, int i)
{
	if (tab[0] == '=' || tab[0] == '+')
		return (export_errors(mini, tmp, tab));
	if (tab[i] == '+' && tab[i + 1] != '=')
		return (export_errors(mini, tmp, tab));
	else
	{
		mini->plus = (tab[i] == '+') ? 2 : 1;
		(*tmp)[0] = ft_strdup(ft_substr(tab, 0, i));
		(*tmp)[1] = ft_strdup("=");
		(*tmp)[2] = ft_strdup(tab + i + mini->plus);
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
	while (tab[i] && tab[i] != '=' && tab[i] != '+')
	{
		if (!ft_isdigit(tab[0]) && (ft_isalnum(tab[i]) || tab[i] == '_'))
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
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(list->key, 1);
		if (*list->symbol)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(list->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		list = list->next;
	}
	mini->cmd_status = 0;
	return ;
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
		mini->plus = 1;
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
	mini->cmd_status = 0;
}
