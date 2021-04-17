/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:50:39 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/16 16:17:15 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_splitted(t_mini *mini)
{
	mini->pwd = NULL;
	mini->oldpwd = NULL;
	mini->pwd = (char **)malloc(sizeof(char *) * 4);
	mini->oldpwd = (char **)malloc(sizeof(char *) * 4);
	mini->oldpwd[0] = ft_strdup("OLDPWD");
	mini->oldpwd[1] = ft_strdup("=");
	mini->oldpwd[3] = NULL;
	mini->pwd[0] = ft_strdup("PWD");
	mini->pwd[1] = ft_strdup("=");
	mini->pwd[3] = NULL;
}

void	change_var(t_mini *mini, int print)
{
	char	cwd[1028];

	mini->oldpwd[2] = ft_strdup(mini->tmp);
	free(mini->tmp);
	if (ft_lstsearch(mini->myenv, "OLDPWD", &mini->print)
		&& mini->print && !print)
		edit_env(mini, mini->oldpwd, 2);
	else if (print == 1)
		edit_env(mini, mini->oldpwd, 1);
	else
		edit_env(mini, mini->oldpwd, 0);
	getcwd(cwd, 1028);
	mini->pwd[2] = ft_strdup(cwd);
	if (ft_lstsearch(mini->myenv, "PWD", &mini->print) && mini->print)
		edit_env(mini, mini->pwd, 2);
	else
		edit_env(mini, mini->pwd, 0);
}

void	changeenv(t_mini *mini, char *path)
{
	int		print;

	init_splitted(mini);
	mini->tmp = ft_strdup(ft_lstsearch(mini->myenv, "PWD", &print));
	if (chdir(path) < 0)
	{
		mini->pwd[2] = ft_strdup("");
		ft_free(&mini->pwd);
		mini->oldpwd[2] = ft_strdup("");
		ft_free(&mini->oldpwd);
		free(mini->tmp);
		return (error_file(mini, path, "cd"));
	}
	change_var(mini, print);
	mini->cmd_status = 0;
	ft_free(&mini->pwd);
	ft_free(&mini->oldpwd);
}

void	cd_home(t_mini *mini)
{
	int		i;

	i = 1;
	if (!mini->tabu[i])
	{
		if (!ft_lstsearch(mini->myenv, "HOME", &mini->print) || mini->print)
			return (error_env(mini, "HOME", "cd"));
		else
			changeenv(mini, ft_lstsearch(mini->myenv, "HOME", &mini->print));
	}
	else if (!ft_strncmp(mini->tabu[i], "-", 1))
	{
		if (!ft_lstsearch(mini->myenv, "OLDPWD", &mini->print) || \
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
	char	*join;
	int		i;

	i = 1;
	if (!mini->tabu[i] || !ft_strncmp(mini->tabu[i], "-", 1))
		return (cd_home(mini));
	else
	{
		join = ft_strjoin(mini->tabu[i], "/");
		dir = opendir(join);
		free(join);
		if (dir)
		{
			closedir(dir);
			changeenv(mini, mini->tabu[i]);
		}
		else
			return (error_file(mini, mini->tabu[i], "cd"));
	}
	mini->cmd_status = 0;
}
