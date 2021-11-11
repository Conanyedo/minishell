/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 09:36:40 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/16 16:17:44 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtins(t_mini *mini)
{
	if (!(ft_strncmp(mini->tabu[0], "env", ft_strlen("env"))))
		return (1);
	else if (!(ft_strncmp(mini->tabu[0], "echo", ft_strlen("echo"))))
		return (1);
	else if (!(ft_strncmp(mini->tabu[0], "pwd", ft_strlen("pwd"))))
		return (1);
	else if (!(ft_strncmp(mini->tabu[0], "cd", ft_strlen("cd"))))
		return (1);
	else if (!(ft_strncmp(mini->tabu[0], "exit", ft_strlen("exit"))))
		return (1);
	else if (!(ft_strncmp(mini->tabu[0], "export", ft_strlen("export"))))
		return (1);
	else if (!(ft_strncmp(mini->tabu[0], "unset", ft_strlen("unset"))))
		return (1);
	return (0);
}

void	do_builtins(t_mini *mini)
{
	if (!(ft_strncmp(mini->tabu[0], "echo", ft_strlen("echo"))))
		ft_echo(mini);
	else if (!(ft_strncmp(mini->tabu[0], "env", ft_strlen("env"))))
		ft_env(mini);
	else if (!(ft_strncmp(mini->tabu[0], "exit", ft_strlen("exit"))))
		ft_exit(mini);
	else if (!(ft_strncmp(mini->tabu[0], "pwd", ft_strlen("pwd"))))
		ft_pwd(mini);
	else if (!(ft_strncmp(mini->tabu[0], "cd", ft_strlen("cd"))))
		ft_cd(mini);
	else if (!(ft_strncmp(mini->tabu[0], "unset", ft_strlen("unset"))))
		ft_unset(mini);
	else if (!(ft_strncmp(mini->tabu[0], "export", ft_strlen("export"))))
		ft_export(mini);
}
