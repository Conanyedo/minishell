/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:24:43 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/13 15:33:11 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	init_env(char **env, t_env **myenv)
{
	t_env	*list;
	char	**splitted;
	int		i;

	*myenv = NULL;
	list = NULL;
	splitted = NULL;
	*myenv = (t_env*)malloc(sizeof(t_env));
	(*myenv)->next = NULL;
	list = *myenv;
	i = 0;
	while (env[i])
	{
		splitted = ft_split(env[i], '=');
		list->key = ft_strdup(splitted[0]);
		if (splitted[1])
			list->value = ft_strdup(splitted[1]);
		ft_free(splitted);
		if (!env[i + 1])
			break ;
		list->next = (t_env*)malloc(sizeof(t_env));
		list = list->next;
		i++;
	}
	list->next = NULL;
}

int		ft_listsize(t_env *env)
{
	t_env	*list;
	int		i;
	
	i = 0;
	list = NULL;
	list = env;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	ft_lsttoarray(t_env *env, char ***tab)
{
	t_env	*list;
	char	*join;
	char	*joined;
	int		i;

	i = 0;
	list = NULL;
	(*tab) = NULL;
	(*tab) = (char **)malloc(sizeof(char*) * (ft_listsize(env) + 1));
	list = env;
	while (list)
	{
		joined = ft_strjoin("=", list->value);
		join = ft_strjoin(list->key, joined);
		free(joined);
		(*tab)[i] = ft_strdup(join);
		free(join);
		i++;
		list = list->next;
	}
	(*tab)[i] = NULL;
}

char	*ft_lstsearch(t_env	*env, char *key)
{
	t_env	*list;

	list = env;
	while (list)
	{
		if (!(ft_strncmp(list->key, key, ft_strlen(key))))
			return (list->value);
		list = list->next;
	}
	return (ft_strdup(""));
}