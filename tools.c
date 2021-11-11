/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:18:49 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/17 14:09:32 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipe(t_mini *mini, t_pipe **pip)
{
	t_pipe	*prev;

	prev = (*pip);
	(*pip) = (*pip)->next;
	if (prev->content)
		free(prev->content);
	free(prev);
	ft_free(&mini->tabu);
	mini->tabu = NULL;
	mini->index += 2;
	mini->p++;
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
		tmp = ft_strdup(ft_strrchr(ft_lstsearch(mini->myenv, "PWD", \
			&mini->print), '/') + 1);
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

void	error_cmd(t_mini *mini)
{
	mini->check.point = 1;
	if_isdirect(mini, mini->tabu[0]);
	if (mini->check.point)
		return ;
	if (!ifexist(mini, 0))
	{
		not_exist(mini);
		if (mini->cmd_status)
			return ;
	}
	else
	{
		stat(mini->tabu[0], &mini->stt);
		if (mini->stt.st_mode & S_IFMT & S_IFDIR)
			return (is_directory(mini, mini->tabu[0]));
		if (!(mini->stt.st_mode & X_OK))
			return (permission(mini, mini->tabu[0]));
	}
	exec_cmd(mini);
}

char	**remove_dust(char ***str)
{
	int		i;
	int		j;
	int		t;
	char	**cpy;

	t = 0;
	while ((*str)[t])
		t++;
	cpy = (char **)malloc(sizeof(char *) * t + 1);
	t = -1;
	while ((*str)[++t])
	{
		cpy[t] = (char *)malloc(sizeof(char) * ft_strlen((*str)[t]) + 1);
		i = -1;
		j = 0;
		while ((*str)[t][++i] != '\0')
			if ((*str)[t][i] > 1)
				cpy[t][j++] = (*str)[t][i];
		cpy[t][j] = '\0';
	}
	cpy[t] = NULL;
	ft_free(str);
	return (cpy);
}
