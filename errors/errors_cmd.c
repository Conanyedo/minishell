/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:36:19 by cabouelw          #+#    #+#             */
/*   Updated: 2021/04/19 11:34:33 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_directory(t_mini *mini, char *file)
{
	mini->cmd_status = 126;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Is a directory\n", 2);
}

void	permission(t_mini *mini, char *file)
{
	mini->cmd_status = 126;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}

void	cmd_not_found(t_mini *mini)
{
	mini->cmd_status = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(mini->tabu[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	error_file(t_mini *mini, char *file, char *cmd)
{
	mini->cmd_status = 1;
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	error_env(t_mini *mini, char *env, char *cmd)
{
	mini->cmd_status = 1;
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(env, 2);
	ft_putstr_fd(" not set\n", 2);
}
