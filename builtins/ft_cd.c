/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:50:39 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/10 19:25:19 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(t_mini *mini)
{
	if (!mini->tab[1])
	{
		if (!ft_lstsearch(mini->myenv, "HOME"))
			ft_putstr_fd("cd: HOME not set\n", 1);
		else
			chdir(ft_lstsearch(mini->myenv, "HOME"));
	}
	else if (mini->tab[1] && mini->tab[1][0] == '-')
		chdir(ft_lstsearch(mini->myenv, "OLDPWD"));
}