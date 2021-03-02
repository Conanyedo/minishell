/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:18:49 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/02 18:35:05 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

t_env   *init_env(char **env)
{
	t_env	*new_env;
	t_env	*fresh;
	int		i;
	char	**splitted;

	splitted = NULL;
	new_env = NULL;
	fresh = NULL;
	if (!(new_env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	new_env->next = NULL;
	fresh = new_env;
	i = 0;
	while (env[i])
	{
		splitted = ft_split(env[i], '=');
		fresh->key = ft_strdup(splitted[0]);
		if (splitted[1])
			fresh->value = ft_strdup(splitted[1]);
		ft_free(splitted);
		if (!env[i + 1])
			break ;
		if (!(fresh->next = (t_env*)malloc(sizeof(t_env))))
			return (NULL);
		fresh = fresh->next;
		i++;
	}
	fresh->next = NULL;
	return (new_env);
}