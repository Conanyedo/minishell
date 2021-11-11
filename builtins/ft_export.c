/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:03:14 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/12 13:12:52 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**export_errors(t_mini *mini, char ***tmp, char *tabu)
{
	ft_free(tmp);
	ft_putstr_fd("export: `", 1);
	ft_putstr_fd(tabu, 1);
	ft_putstr_fd("\': not a valid identifier\n", 1);
	mini->cmd_status = 1;
	(*tmp) = NULL;
	return (NULL);
}

char	**filling(t_mini *mini, char ***tmp, char *tabu, int i)
{
	if (tabu[0] == '=' || tabu[0] == '+')
		return (export_errors(mini, tmp, tabu));
	else if (tabu[i] == '+' && tabu[i + 1] != '=')
		return (export_errors(mini, tmp, tabu));
	else
	{
		mini->plus = 1;
		if (tabu[i] == '+')
			mini->plus = 2;
		(*tmp)[0] = ft_substr(tabu, 0, i);
		(*tmp)[1] = ft_strdup("=");
		(*tmp)[2] = ft_strdup(tabu + i + mini->plus);
		(*tmp)[3] = NULL;
	}
	return (*tmp);
}

char	**split_env(t_mini *mini, char *tabu)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	tmp = (char **)malloc(sizeof(char *) * 4);
	while (tabu[i] && tabu[i] != '=' && tabu[i] != '+')
	{
		if (!ft_isdigit(tabu[0]) && (ft_isalnum(tabu[i]) || tabu[i] == '_'))
			i++;
		else
			return (export_errors(mini, &tmp, tabu));
	}
	if (!tabu[i])
	{
		tmp[0] = ft_strdup(tabu);
		tmp[1] = ft_strdup("");
		tmp[2] = ft_strdup("");
		tmp[3] = NULL;
		return (tmp);
	}
	return (filling(mini, &tmp, tabu, i));
}

void	add_env(t_mini *mini, char **splitted)
{
	t_env	*list;

	list = NULL;
	list = mini->myenv;
	while (list->next)
		list = list->next;
	list->next = (t_env *)malloc(sizeof(t_env));
	list = list->next;
	list->key = ft_strdup(splitted[0]);
	list->symbol = ft_strdup(splitted[1]);
	list->value = ft_strdup(splitted[2]);
	list->print = 0;
	list->next = NULL;
}

void	ft_export(t_mini *mini)
{
	int		i;
	char	**splitted;

	i = 1;
	splitted = NULL;
	if (!mini->tabu[i])
		return (print_export(mini));
	while (mini->tabu[i])
	{
		mini->plus = 1;
		splitted = split_env(mini, mini->tabu[i]);
		if (!splitted)
			return ;
		if (ft_lstsearch(mini->myenv, splitted[0], &mini->print))
			edit_env(mini, splitted, 0);
		else
			add_env(mini, splitted);
		ft_free(&splitted);
		i++;
	}
	mini->cmd_status = 0;
}
