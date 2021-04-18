/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:35:56 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/17 17:08:47 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ifexist(t_mini *mini, int i)
{
	char	*slashcmd;

	mini->paths = NULL;
	mini->path_value = ft_lstsearch(mini->myenv, "PATH", &mini->print);
	if (mini->path_value)
		mini->paths = ft_split(mini->path_value, ':');
	slashcmd = ft_strjoin("/", mini->tabu[0]);
	while (mini->paths[i] && !mini->print)
	{
		mini->cmd_exist = ft_strjoin(mini->paths[i], slashcmd);
		if (!stat(mini->cmd_exist, &mini->stt) && S_ISREG(mini->stt.st_mode))
		{
			free(mini->tabu[0]);
			mini->tabu[0] = ft_strdup(mini->cmd_exist);
			free(slashcmd);
			ft_free(&mini->paths);
			free(mini->cmd_exist);
			return (1);
		}
		free(mini->cmd_exist);
		i++;
	}
	free(slashcmd);
	ft_free(&mini->paths);
	return (0);
}

void	not_exist(t_mini *mini)
{
	if (*mini->tabu[0] == '.' || *mini->tabu[0] == '/')
	{
		if (stat(mini->tabu[0], &mini->stt))
			return (error_file(mini, mini->tabu[0], ""));
		if (mini->stt.st_mode & S_IFMT & S_IFDIR)
			return (is_directory(mini, mini->tabu[0]));
		if (!(mini->stt.st_mode & X_OK))
			return (permission(mini, mini->tabu[0]));
	}
	else
	{
		if (*mini->tabu[0] == '/')
			return (is_directory(mini, mini->tabu[0]));
		else if (!*mini->tabu[0])
			return (cmd_not_found(mini));
		else if (!stat(mini->tabu[0], &mini->stt) && (mini->stt.st_mode & X_OK))
			mini->cmd_status = 0;
		else if (*mini->tabu[0] && (*mini->tabu[0] == '='
				|| !ft_strchr(mini->tabu[0], '=')))
			return (cmd_not_found(mini));
	}
	mini->cmd_status = 0;
}

void	pipe_handler(t_mini *mini, t_pipe *pip, int pipes)
{
	int		i;

	mini->pidpipe[mini->p] = fork();
	if (!mini->pidpipe[mini->p])
	{
		if (pip->next && !mini->fd[1])
			dup2(mini->pipefds[mini->index + 1], 1);
		if (mini->index && (!mini->fd[0] || (!mini->tabu[1] && !mini->fd[0])))
			dup2(mini->pipefds[mini->index - 2], 0);
		i = -1;
		while (++i < (pipes * 2))
			close(mini->pipefds[i]);
		if (mini->tabu[0] && is_builtins(mini))
		{
			do_builtins(mini);
			exit (mini->cmd_status);
		}
		else if (mini->tabu[0])
		{
			error_cmd(mini);
			exit (mini->cmd_status);
		}
	}
}

void	commands(t_mini *mini, t_cmd *cmd, t_pipe *pip)
{
	if (mini->redir.err)
		return ;
	if (cmd->pipes)
		pipe_handler(mini, pip, cmd->pipes);
	else
	{
		if (mini->tabu[0] && is_builtins(mini))
			do_builtins(mini);
		else if (mini->tabu[0])
			error_cmd(mini);
	}
	close_fd(mini);
	dup2(mini->oldoutput, 1);
	dup2(mini->oldinput, 0);
	underscore(mini);
}

void	exec_cmd(t_mini *mini)
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
		exit(execve(mini->tabu[0], mini->tabu, mini->env_array));
}
