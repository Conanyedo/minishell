/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:24:43 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/12 13:08:06 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(char **env, t_env **myenv)
{
	t_env	*list;
	char	**splitted;
	int		i;

	*myenv = (t_env *)malloc(sizeof(t_env));
	(*myenv)->next = NULL;
	list = *myenv;
	i = -1;
	while (env[++i])
	{
		splitted = ft_split(env[i], '=');
		list->print = 0;
		list->key = ft_strdup(splitted[0]);
		if (splitted[1])
		{
			list->symbol = ft_strdup("=");
			list->value = ft_strdup(splitted[1]);
		}
		ft_free(&splitted);
		if (!env[i + 1])
			break ;
		list->next = (t_env *)malloc(sizeof(t_env));
		list = list->next;
	}
	list->next = NULL;
}

int	ft_listsize(t_env *env)
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

void	ft_lsttoarray(t_env *env, char ***tabu)
{
	t_env	*list;
	char	*join;
	char	*joined;
	int		i;

	i = 0;
	list = NULL;
	(*tabu) = NULL;
	(*tabu) = (char **)malloc(sizeof(char *) * (ft_listsize(env) + 1));
	list = env;
	while (list)
	{
		joined = ft_strjoin("=", list->value);
		join = ft_strjoin(list->key, joined);
		free(joined);
		(*tabu)[i] = ft_strdup(join);
		free(join);
		i++;
		list = list->next;
	}
	(*tabu)[i] = NULL;
}

char	*ft_lstsearch(t_env *env, char *key, int *print)
{
	t_env	*list;

	list = env;
	while (list)
	{
		if (!(ft_strncmp(list->key, key, ft_strlen(key))))
		{
			*print = list->print;
			return (list->value);
		}
		list = list->next;
	}
	return (NULL);
}
