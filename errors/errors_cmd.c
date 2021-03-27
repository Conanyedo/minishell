/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:36:19 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/25 12:10:56 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_directory(t_mini *mini)
{
	mini->cmd_status = 126;
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(mini->tab[0], 1);
	ft_putstr_fd(": is a directory\n", 1);
}

void	permission(t_mini *mini)
{
	mini->cmd_status = 126;
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(mini->tab[0], 1);
	ft_putstr_fd(": Permission denied\n", 1);
}

void	cmd_not_found(t_mini *mini)
{
	mini->cmd_status = 127;
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(mini->tab[0], 1);
	ft_putstr_fd(": command not found\n", 1);
}

void	error_file(t_mini *mini, char *file, char *cmd)
{
	mini->cmd_status = 1;
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(file, 1);
	ft_putstr_fd(": No such file or directory\n", 1);
}

void	error_env(t_mini *mini, char *env, char *cmd)
{
	mini->cmd_status = 1;
	ft_putstr_fd("minishell: ", 1);
	if (cmd)
	{
		ft_putstr_fd(cmd, 1);
		ft_putstr_fd(": ", 1);
	}
	ft_putstr_fd(env, 1);
	ft_putstr_fd(" not set\n", 1);
}
