/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:02:23 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/28 13:03:00 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	edit(t_mini *mini, t_env **list, char ***splitted, int print)
{
	char	*tmp;

	tmp = ft_strdup("");
	if (*(*list)->symbol == '=')
		ft_strlcpy((*list)->symbol, "=", 2);
	else
		ft_strlcpy((*list)->symbol, (*splitted)[1], 2);
	if (*(*splitted)[1])
	{
		if (mini->plus == 2)
		{
			tmp = ft_strjoin((*list)->value, (*splitted)[2]);
			free((*list)->value);
			free((*splitted)[2]);
			(*splitted)[2] = ft_strdup(tmp);
		}
		else
			free((*list)->value);
		(*list)->print = print;
		(*list)->value = ft_strdup((*splitted)[2]);
	}
	free(tmp);
}

void	edit_env(t_mini *mini, char **splitted, int print)
{
	t_env	*list;

	list = NULL;
	if (!ft_strncmp("_", splitted[0], ft_strlen(splitted[0])))
		return ;
	list = mini->myenv;
	while (list)
	{
		if (!(ft_strncmp(list->key, splitted[0], ft_strlen(splitted[0]))))
			edit(mini, &list, &splitted, print);
		list = list->next;
	}
}

void	print_underscore(t_mini *mini, t_env *list)
{
	char	*tmp;

	tmp = NULL;
	ft_free(mini->env_array);
	mini->env_array = NULL;
	if (!ft_strncmp(list->key, "_", 1) && ft_strrchr(list->value, '/'))
	{
		tmp = ft_strdup(ft_strrchr(list->value, '/') + 1);
		if (!ft_strncmp(tmp, "minishell", 10))
		{
			ft_putstr_fd("declare -x _=\"", 1);
			ft_putstr_fd(list->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
	}
}

void	print_value(char *value)
{
	int		i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '"')
			ft_putchar_fd('\\', 1);
		ft_putchar_fd(value[i], 1);
		i++;
	}
}

void	print_export(t_mini *mini)
{
	t_env	*sorted;

	insertionsort(mini, &sorted);
	while (sorted)
	{
		if (ft_strncmp(sorted->key, "_", 1) && !sorted->print)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(sorted->key, 1);
			if (*sorted->symbol)
			{
				ft_putstr_fd("=\"", 1);
				print_value(sorted->value);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
		print_underscore(mini, sorted);
		sorted = sorted->next;
	}
	mini->cmd_status = 0;
	return ;
}
