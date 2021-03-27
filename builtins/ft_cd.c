/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:50:39 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/25 13:16:48 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_splitted(char ***oldpwd, char ***pwd)
{
	*pwd = (char **)malloc(sizeof(char *) * 4);
	*oldpwd = (char **)malloc(sizeof(char *) * 4);
	(*oldpwd)[0] = ft_strdup("OLDPWD");
	(*oldpwd)[1] = ft_strdup("=");
	(*oldpwd)[3] = NULL;
	(*pwd)[0] = ft_strdup("PWD");
	(*pwd)[1] = ft_strdup("=");
	(*pwd)[3] = NULL;
}

void	changeenv(t_mini *mini, char *path, char ***oldpwd, char ***pwd)
{
	char	cwd[1028];

	getcwd(cwd, 1028);
	chdir(path);
	(*oldpwd)[2] = ft_strdup(cwd);
	if (ft_lstsearch(mini->myenv, "OLDPWD"))
		edit_env(mini, *oldpwd);
	else
		add_env(mini, *oldpwd);
	getcwd(cwd, 1028);
	(*pwd)[2] = ft_strdup(cwd);
	if (ft_lstsearch(mini->myenv, "PWD"))
		edit_env(mini, *pwd);
	else
		add_env(mini, *pwd);
}

void	cd_home(t_mini *mini, char ***oldpwd, char ***pwd)
{
	int		i;

	i = 1;
	if (!mini->tab[i])
	{
		if (!ft_lstsearch(mini->myenv, "HOME"))
			error_env(mini, "HOME", "cd");
		else
			changeenv(mini, ft_lstsearch(mini->myenv, "HOME"), oldpwd, pwd);
	}
	else if (!ft_strncmp(mini->tab[i], "-", 1))
	{
		if (!ft_lstsearch(mini->myenv, "OLDPWD"))
			error_env(mini, "OLDPWD", "cd");
		else
		{
			changeenv(mini, ft_lstsearch(mini->myenv, "OLDPWD"), oldpwd, pwd);
			ft_putstr_fd((*pwd)[2], 1);
			ft_putstr_fd("\n", 1);
		}
	}
}

void	ft_cd(t_mini *mini)
{
	DIR		*dir;
	char	**pwd;
	char	**oldpwd;
	int		i;

	i = 1;
	init_splitted(&oldpwd, &pwd);
	if (!mini->tab[i] || !ft_strncmp(mini->tab[i], "-", 1))
		cd_home(mini, &oldpwd, &pwd);
	else
	{
		dir = opendir(ft_strjoin(mini->tab[i], "/"));
		if (dir)
		{
			closedir(dir);
			changeenv(mini, mini->tab[i], &oldpwd, &pwd);
		}
		else
			return (error_file(mini, mini->tab[i], "cd"));
	}
	mini->cmd_status = 0;
	ft_free(pwd);
	ft_free(oldpwd);
}
