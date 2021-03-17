/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:18:49 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/14 17:42:33 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		checksymbol(char *tab, int i)
{
	while (tab[i] && (ft_isalnum(tab[i]) || tab[i] == '_'))
		i++;
	return (i);
}

void	trimming_quotes(char *tab)
{
	char	*tmp;
	
	tmp = NULL;
	if (tab[0] == '\"')
		tmp = ft_strtrim(tab, "\"");
	else if (tab[0] == '\'')
		tmp = ft_strtrim(tab, "\'");
	if (tmp)
	{
		ft_strlcpy(tab, tmp, ft_strlen(tmp) + 1);
		free(tmp);
	}
}

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

void    exec_cmd(t_mini *mini)
{
	ft_lsttoarray(mini->myenv, &mini->env_array);
	mini->pid = fork();
	if (mini->pid > 0)
		wait(NULL);
	else
		execve(mini->tab[0], mini->tab, mini->env_array);
}