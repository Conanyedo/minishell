/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:18:49 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/09 11:25:14 by ybouddou         ###   ########.fr       */
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

char	*ft_lstsearch(t_env	*env, char *to_search)
{
	t_env	*fresh;

	fresh = env;
	while (fresh != NULL)
	{
		if (!(ft_strncmp(fresh->key, to_search, ft_strlen(to_search))))
			return (fresh->value);
		fresh = fresh->next;
	}
	return (NULL);
}

void	prompt(t_mini *mini)
{
	char	buff[1028];
	char	*ptr;
	char	*tmp;

	ptr = getcwd(buff, 1028);
	tmp = NULL;
	if (mini->status == 0)
		ft_putstr_fd("\033[1;32m", 1);
	else
		ft_putstr_fd("\033[1;31m", 1);
	if (ptr == NULL)
		tmp = ft_strdup(ft_strrchr(ft_lstsearch(mini->myenv, "PWD"), '/') + 1);
	else
	{
		if (!ft_strncmp(ptr, "/", ft_strlen(ptr)))
			tmp = ft_strdup(ptr);
		else
			tmp = ft_strdup(ft_strrchr(ptr, '/') + 1);
	}
	ft_putstr_fd("➜  \033[1;34m", 1);//6
	ft_putstr_fd(tmp, 1);
	if (mini->status == 0)
		ft_putstr_fd("\033[1;32m $>", 1);
	else
		ft_putstr_fd("\033[1;31m $>", 1);
	ft_putstr_fd("\033[0m ", 1);
	free(tmp);
	mini->status = 0;
}

void	init_env(char **env, t_env **myenv)
{
	t_env	*fresh;
	char	**splitted;
	int		i;

	*myenv = NULL;
	fresh = NULL;
	splitted = NULL;
	*myenv = (t_env*)malloc(sizeof(t_env));
	(*myenv)->next = NULL;
	fresh = *myenv;
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
		fresh->next = (t_env*)malloc(sizeof(t_env));
		fresh = fresh->next;
		i++;
	}
	fresh->next = NULL;
}

void    exec_cmd(t_mini *mini, char **env)
{
	mini->pid = fork();
	if (mini->pid > 0)
		wait(NULL);
	else
	{
		*mini->argv = mini->input;
		mini->argv[1] = NULL;
		execve(mini->input, mini->argv, env);
	}
}