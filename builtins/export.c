/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:02:23 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/25 15:40:26 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (mini->plus == 2)
		{
			tmp = ft_strjoin((*list)->value, (*splitted)[2]);
			free((*list)->value);
			free((*splitted)[2]);
			(*splitted)[2] = ft_strdup(tmp);
		}
		else
			free((*list)->value);
		(*list)->value = ft_strdup((*splitted)[2]);
	}
	free(tmp);
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
			edit(mini, &list, &splitted);
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
	t_env	*list;

	ft_lsttoarray(mini->myenv, &mini->env_array);
	sortarray(mini, &mini->env_array);
	init_env(mini->env_array, &list);
	while (list)
	{
		if (ft_strncmp(list->key, "_", 1))
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(list->key, 1);
			if (*list->symbol)
			{
				ft_putstr_fd("=\"", 1);
				print_value(list->value);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
		print_underscore(mini, list);
		list = list->next;
	}
	mini->cmd_status = 0;
	return ;
}
