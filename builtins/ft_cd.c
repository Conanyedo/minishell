/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:50:39 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/28 14:08:44 by ybouddou         ###   ########.fr       */
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

void	changeenv(t_mini *mini, char *path)
{
	char	cwd[1028];
	char	**pwd;
	char	**oldpwd;
	char	*tmp;
	int		print;

	init_splitted(&oldpwd, &pwd);
	tmp = ft_strdup(ft_lstsearch(mini->myenv, "PWD", &print));
	if (chdir(path) < 0)
		return (error_file(mini, path, "cd"));
	oldpwd[2] = ft_strdup(tmp);
	free(tmp);
	if (ft_lstsearch(mini->myenv, "OLDPWD", &mini->print)
		&& mini->print && !print)
		edit_env(mini, oldpwd, 2);
	else if (print == 1)
		edit_env(mini, oldpwd, 1);
	else
		edit_env(mini, oldpwd, 0);
	getcwd(cwd, 1028);
	pwd[2] = ft_strdup(cwd);
	if (ft_lstsearch(mini->myenv, "PWD", &mini->print) && mini->print)
		edit_env(mini, pwd, 2);
	else
		edit_env(mini, pwd, 0);
	mini->cmd_status = 0;
}

void	cd_home(t_mini *mini)
{
	int		i;

	i = 1;
	if (!mini->tab[i])
	{
		if (!ft_lstsearch(mini->myenv, "HOME", &mini->print) || mini->print)
			return (error_env(mini, "HOME", "cd"));
		else
			changeenv(mini, ft_lstsearch(mini->myenv, "HOME", &mini->print));
	}
	else if (!ft_strncmp(mini->tab[i], "-", 1))
	{
		if (!ft_lstsearch(mini->myenv, "OLDPWD", &mini->print) ||
			mini->print == 1)
			return (error_env(mini, "OLDPWD", "cd"));
		else
		{
			changeenv(mini, ft_lstsearch(mini->myenv, "OLDPWD", &mini->print));
			if (mini->cmd_status)
				return ;
			ft_putstr_fd(ft_lstsearch(mini->myenv, "PWD", &mini->print), 1);
			ft_putstr_fd("\n", 1);
		}
	}
}

void	ft_cd(t_mini *mini)
{
	DIR		*dir;
	int		i;

	i = 1;
	if (!mini->tab[i] || !ft_strncmp(mini->tab[i], "-", 1))
		return (cd_home(mini));
	else
	{
		dir = opendir(ft_strjoin(mini->tab[i], "/"));
		if (dir)
		{
			closedir(dir);
			changeenv(mini, mini->tab[i]);
		}
		else
			return (error_file(mini, mini->tab[i], "cd"));
	}
	mini->cmd_status = 0;
}
