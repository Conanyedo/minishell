/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:50:39 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/11 10:31:01 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(t_mini *mini)
{
	DIR		*dir;
	
	mini->tab++;
	if (!*mini->tab)
	{
		if (!ft_lstsearch(mini->myenv, "HOME"))
			ft_putstr_fd("cd: HOME not set\n", 1);
		else
			chdir(ft_lstsearch(mini->myenv, "HOME"));
	}
	else if (*mini->tab && **mini->tab == '-')
		chdir(ft_lstsearch(mini->myenv, "OLDPWD"));
	else
	{
		dir = opendir(*mini->tab);
		if (dir)
		{
			closedir(dir);
			chdir(*mini->tab);
		}
		else
		{
			ft_putstr_fd("No such file or directory\n", 1);
			mini->status = 1;
			return ;
		}
	}
}