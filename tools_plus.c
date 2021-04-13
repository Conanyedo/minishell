/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:39:04 by cabouelw          #+#    #+#             */
/*   Updated: 2021/04/13 12:56:59 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_mini *mini)
{
	if (mini->fd[1])
	{
		close(mini->fd[1]);
		mini->fd[1] = 0;
	}
	if (mini->fd[0])
	{
		close(mini->fd[0]);
		mini->fd[0] = 0;
	}
}

int	isredirect_loop(t_mini *mini, char *s, int i)
{
	int		point;

	while (s[i] == '/' || s[i] == '.')
	{
		point = 0;
		while (s[i] == '.')
		{
			if (point > 1)
			{
				error_file(mini, s, "");
				return (-1);
			}
			point++;
			i++;
		}
		i++;
	}
	return (i);
}

void	pipe_handler(t_mini *mini, t_pipe *pip)
{
	if (!mini->ret && pip->next)
	{
		mini->ret = 1;
		if (!pipe(mini->pipe))
			mini->ret = 1;
		if (!mini->fd[1])
			dup2(mini->pipe[1], 1);
		close(mini->pipe[1]);
	}
	else if (mini->ret)
	{
		if (!mini->fd[0] || (!mini->tabu[1] && !mini->fd[0]))
			dup2(mini->pipe[0], 0);
		close(mini->pipe[0]);
		mini->ret = 0;
		if (pip->next)
		{
			if (!pipe(mini->pipe))
				mini->ret = 1;
			if (!mini->fd[1])
				dup2(mini->pipe[1], 1);
			close(mini->pipe[1]);
		}
	}
}

void	ft_dup(t_mini *mini)
{
	mini->oldinput = dup(0);
	mini->oldoutput = dup(1);
}

void	exec_cmdplus(t_mini *mini)
{
	mini->cmd_status = 0;
	ft_lsttoarray(mini->myenv, &mini->env_array);
	mini->pid = fork();
	if (mini->pid > 0)
	{
		waitpid(mini->pid, &mini->r, 0);
		if (WEXITSTATUS(mini->r))
			mini->cmd_status = WEXITSTATUS(mini->r);
		mini->pid = 0;
		ft_free(&mini->env_array);
	}
	else
		execve(mini->tabu[0], mini->tabu, mini->env_array);
}
