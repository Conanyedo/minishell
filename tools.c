/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:18:49 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/22 16:28:47 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **arr)
{
	int		i;

	i = 0;
	while (arr && arr[i])
	{
		if (arr[i])
			free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	if (arr)
		free(arr);
	arr = NULL;
}

void	git(char *tmp)
{
	int		fd;
	DIR		*dir;
	char	*temp;

	tmp = NULL;
	dir = opendir(".git");
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd("\033[1;36mgit:(", 1);
		fd = open(".git/HEAD", O_RDONLY, 0666);
		get_next_line(fd, &tmp);
		temp = ft_strdup(ft_strrchr(tmp, '/') + 1);
		free(tmp);
		ft_putstr_fd("\033[1;31m", 1);
		ft_putstr_fd(temp, 1);
		ft_putstr_fd("\033[1;36m) \033[0m", 1);
		free(temp);
		close(fd);
	}
}

void	prompt(t_mini *mini)
{
	char	*tmp;

	tmp = NULL;
	tmp = getcwd(mini->buff, 1028);
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
	if (!ifexist(mini))
	{
		if (*mini->tab[0] == '.' && mini->tab[0][1] == '/')
		{
			if (stat(mini->tab[0], &mini->stats))
				return (cmd_not_found(mini));
			if (mini->stats.st_mode & S_IFMT & S_IFDIR)
				return (is_directory(mini));
			if (!(mini->stats.st_mode & X_OK))
				return (permission(mini));
		}
		else
		{
			if (*mini->tab[0] == '/')
				return (is_directory(mini));
			return (cmd_not_found(mini));
		}
	}
	else
	{
		stat(mini->tab[0], &mini->stats);
		if (mini->stats.st_mode & S_IFMT & S_IFDIR)
			return (is_directory(mini));
		if (!(mini->stats.st_mode & X_OK))
			return (permission(mini));
	}
	mini->cmd_status = 0;
	ft_lsttoarray(mini->myenv, &mini->env_array);
	mini->pid = fork();
	if (mini->pid > 0)
	{
		wait(NULL);
		mini->pid = 0;
	}
	else
		execve(mini->tab[0], mini->tab, mini->env_array);
}
