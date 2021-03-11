/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 09:36:40 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/10 19:22:35 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtins(t_mini *mini)
{
	if (!(ft_strncmp(mini->tab[0], "env", ft_strlen(mini->tab[0]))))
		return (1);
	else if (!(ft_strncmp(mini->tab[0], "echo", ft_strlen(mini->tab[0]))))
		return (1);
	else if (!(ft_strncmp(mini->tab[0], "pwd", ft_strlen(mini->tab[0]))))
		return (1);
	else if (!(ft_strncmp(mini->tab[0], "cd", ft_strlen(mini->tab[0]))))
		return (1);
	else if (!(ft_strncmp(mini->tab[0], "exit", ft_strlen(mini->tab[0]))))
		return (1);
	else if (!(ft_strncmp(mini->tab[0], "export", ft_strlen(mini->tab[0]))))
		return (1);
	else if (!(ft_strncmp(mini->tab[0], "unset", ft_strlen(mini->tab[0]))))
		return (1);
	return (0);
}

void	do_builtins(t_mini *mini)
{
	if (!*mini->tab[0])
		return ;
	if (!(ft_strncmp(mini->tab[0], "echo", ft_strlen(mini->tab[0]))))
		ft_echo(mini->tab);
	else if (!(ft_strncmp(mini->tab[0], "env", ft_strlen(mini->tab[0]))))
		ft_env(mini->myenv);
	else if (!(ft_strncmp(mini->tab[0], "exit", ft_strlen(mini->tab[0]))))
		ft_exit(mini);
	else if (!(ft_strncmp(mini->tab[0], "pwd", ft_strlen(mini->tab[0]))))
		ft_pwd(mini);
	else if (!(ft_strncmp(mini->tab[0], "cd", ft_strlen(mini->tab[0]))))
		ft_cd(mini);
	else if (!(ft_strncmp(mini->tab[0], "unset", ft_strlen(mini->tab[0]))))
		ft_unset(mini);
	else if (!(ft_strncmp(mini->tab[0], "export", ft_strlen(mini->tab[0]))))
		ft_export(mini);
	
}