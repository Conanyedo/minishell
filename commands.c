/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:35:56 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/25 17:49:58 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ifexist(t_mini *mini)
{
	int		i;
	char	*slashcmd;

	i = 0;
	mini->path_value = ft_lstsearch(mini->myenv, "PATH");
	mini->paths = (mini->path_value) ? ft_split(mini->path_value, ':') : NULL;
	slashcmd = ft_strjoin("/", mini->tab[0]);
	while (mini->paths[i])
	{
		mini->cmd_exist = ft_strjoin(mini->paths[i], slashcmd);
		if (!stat(mini->cmd_exist, &mini->stt) && S_ISREG(mini->stt.st_mode))
		{
			free(mini->tab[0]);
			mini->tab[0] = ft_strdup(mini->cmd_exist);
			free(slashcmd);
			ft_free(mini->paths);
			free(mini->cmd_exist);
			return (1);
		}
		free(mini->cmd_exist);
		i++;
	}
	free(slashcmd);
	ft_free(mini->paths);
	return (0);
}

void	not_exist(t_mini *mini)
{
	if (*mini->tab[0] == '.' || *mini->tab[0] == '/')
	{
		if (stat(mini->tab[0], &mini->stt))
			return (error_file(mini, mini->tab[0], ""));
		if (mini->stt.st_mode & S_IFMT & S_IFDIR)
			return (is_directory(mini));
		if (!(mini->stt.st_mode & X_OK))
			return (permission(mini));
	}
	else
	{
		if (*mini->tab[0] == '/')
			return (is_directory(mini));
		else if (*mini->tab[0] == '=' || !ft_strchr(mini->tab[0], '='))
			return (cmd_not_found(mini));
		return ;
	}
}

void	if_isdirect(t_mini *mini, char *s)
{
	int		i;
	int		point;

	i = 0;
	while (s[i] == '.')
		i++;
	if (i == 1 && !s[i])
		return (error_arg(mini));
	if (i && (!s[i] || s[i] != '/'))
		return (cmd_not_found(mini));
	while (s[i] == '/' || s[i] == '.')
	{
		point = 0;
		while (s[i] == '.')
		{
			if (point > 1)
				return (error_file(mini, s, ""));
			point++;
			i++;
		}
		i++;
	}
	if (!s[i])
		return (is_directory(mini));
	mini->check.point = 0;
}

void	commands(t_mini *mini)
{
	if (mini->redir.err)
		return ;
	if (is_builtins(mini))
		do_builtins(mini);
	else
		exec_cmd(mini);
	if (mini->fd[1])
    {
        close(mini->fd[1]);
        mini->fd[1] = 0;
        dup2(mini->redir.oldoutput, 1);
        close(mini->redir.oldoutput);
        mini->redir.oldoutput = 0;
    }
    if (mini->fd[0])
    {
        close(mini->fd[0]);
        mini->fd[0] = 0;
        dup2(mini->redir.oldinput, 0);
        close(mini->redir.oldinput);
        mini->redir.oldinput = 0;
    }
	underscore(mini);
}
