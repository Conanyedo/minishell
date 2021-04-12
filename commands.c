/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:35:56 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/12 15:23:03 by cabouelw         ###   ########.fr       */
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
	while (mini->paths[i])
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
			return (is_directory(mini));
		if (!(mini->stt.st_mode & X_OK))
			return (permission(mini, mini->tabu[0]));
	}
	else
	{
		if (*mini->tabu[0] == '/')
			return (is_directory(mini));
		else if (!*mini->tabu[0])
			return (cmd_not_found(mini));
		else if (*mini->tabu[0] && (*mini->tabu[0] == '='
				|| !ft_strchr(mini->tabu[0], '=')))
			return (cmd_not_found(mini));
	}
}

void	if_isdirect(t_mini *mini, char *s)
{
	int		i;

	i = 0;
	if (stat(s, &mini->stt) && s[0] == '/')
		return (error_file(mini, s, ""));
	if (mini->stt.st_mode & S_IFMT & S_IFDIR && s[0] == '/')
		return (is_directory(mini));
	while (s[i] == '.')
		i++;
	if (i == 1 && !s[i])
		return (error_arg(mini));
	if (i && (!s[i] || s[i] != '/'))
		return (cmd_not_found(mini));
	i = isredirect_loop(mini, s, i);
	if (i == -1)
		return ;
	if (!s[i] && i)
		return (is_directory(mini));
	mini->check.point = 0;
}

void	commands(t_mini *mini, t_pipe *pip)
{
	if (mini->redir.err)
		return ;
	commands_tools(mini, pip);
	if (mini->tabu[0] && is_builtins(mini))
		do_builtins(mini);
	else if (mini->tabu[0])
		exec_cmd(mini);
	dup2(mini->oldoutput, 1);
	dup2(mini->oldinput, 0);
	close_fd(mini);
	underscore(mini);
}
