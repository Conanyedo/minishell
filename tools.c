/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:18:49 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/19 16:39:03 by cabouelw         ###   ########.fr       */
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

void	git(char *tmp)
{
	int		fd;
	DIR		*dir;

	tmp = NULL;
	dir = opendir(".git");
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd("\033[1;36mgit:(", 1);
		fd = open(".git/HEAD", O_RDONLY, 0666);
		get_next_line(fd, &tmp);
		tmp = ft_strdup(ft_strrchr(tmp, '/') + 1);
		ft_putstr_fd("\033[1;31m", 1);
		ft_putstr_fd(tmp, 1);
		ft_putstr_fd("\033[1;36m) \033[0m", 1);
		free(tmp);
		close(fd);
	}
}

void	prompt(t_mini *mini)
{
	char	*tmp;

	tmp = getcwd(mini->buff, 1028);
	tmp = NULL;
	if (mini->status)
		mini->cmd_status = 258;
	if (mini->status == 0 && mini->cmd_status == 0)
		ft_putstr_fd("\033[1;32m➜  \033[1;34m", 1);
	else
		ft_putstr_fd("\033[1;31m➜  \033[1;34m", 1);
	if (tmp == NULL)
		tmp = ft_strdup(ft_strrchr(ft_lstsearch(mini->myenv, "PWD"), '/') + 1);
	else
	{
		if (!ft_strncmp(tmp, "/", ft_strlen(tmp)))
			tmp = ft_strdup(tmp);
		else
			tmp = ft_strdup(ft_strrchr(tmp, '/') + 1);
	}
	ft_putstr_fd(tmp, 1);
	free(tmp);
	ft_putstr_fd(" \033[0m", 1);
	git(tmp);
	mini->status = 0;
}

void	exec_cmd(t_mini *mini)
{
	int		fd;

	if (!ifexist(mini))
	{
		if ((fd = open(mini->tab[0], O_RDONLY)) < 0)
			return (cmd_not_found(mini));
	}
	mini->cmd_status = 0;
	ft_lsttoarray(mini->myenv, &mini->env_array);
	mini->pid = fork();
	if (mini->pid > 0)
		wait(NULL);
	else
		execve(mini->tab[0], mini->tab, mini->env_array);
}

char	**remove_dust(char **str)
{
	int		i;
	int		j;
	int		t;
	char	**cpy;

	t = 0;
	while (str[t])
		t++;
	cpy = (char**)malloc(sizeof(char*) * t + 1);
	t = -1;
	while (str[++t])
	{
		cpy[t] = (char*)malloc(sizeof(char) * ft_strlen(str[t]) + 1);
		i = -1;
		j = 0;
		while (str[t][++i] != '\0')
			if (str[t][i] > 0)
				cpy[t][j++] = str[t][i];
		cpy[t][j] = '\0';
	}
	cpy[t] = NULL;
	return (cpy);
}
