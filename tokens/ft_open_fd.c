/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 11:56:25 by cabouelw          #+#    #+#             */
/*   Updated: 2021/04/19 11:32:09 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_right_open(t_mini *mini, int i)
{
	if (mini->redir.fd[1])
		close(mini->redir.fd[1]);
	if (mini->redir.opn)
		mini->redir.fd[1] = open(mini->redir.tmpfile, \
			O_CREAT | O_RDWR | O_APPEND, 0666);
	else
		mini->redir.fd[1] = open(mini->redir.tmpfile, \
			O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (mini->redir.fd[1] < 0)
	{
		stat(mini->redir.tmpfile, &mini->stt);
		mini->redir.len = -1;
		if (!mini->redir.tmpfile[0] && mini->check.tmp != NULL)
			ambiguous(mini, mini->check.tmp);
		else if (mini->stt.st_mode & S_IFMT & S_IFDIR)
			is_directory(mini, mini->redir.tmpfile);
		else if (ft_strchr(mini->redir.tmpfile + 1, '/') || \
			!*mini->redir.tmpfile)
			error_file(mini, mini->redir.tmpfile, "");
		else
			permission(mini, mini->redir.tmpfile);
		mini->redir.err = 1;
	}
	mini->redir.opn = 0;
	return (i);
}

void	redir_left_open(t_mini *mini)
{
	mini->redir.fd[0] = open(mini->redir.file, O_RDONLY);
	if (mini->redir.fd[0] < 0)
	{
		mini->redir.len = -1;
		stat(mini->redir.file, &mini->stt);
		if (!(mini->stt.st_mode & R_OK))
			permission(mini, mini->redir.file);
		else
			error_file(mini, mini->redir.file, "");
		mini->redir.err = 1;
	}
}

int	redir_right(t_mini *mini, int i, char t)
{
	if (mini->redir.str[i + 1] == '>')
		mini->redir.opn = 1;
	while (mini->redir.str[i] == '>')
		i++;
	ft_memset(mini->redir.tmpfile, '\0', mini->redir.len);
	mini->redir.len = 0;
	while (mini->redir.str[i] == ' ')
		i++;
	i = cutfilename(mini, i, t, &mini->redir.tmpfile);
	return (redir_right_open(mini, i));
}

int	redir_left(t_mini *mini, int i, char t)
{
	if (mini->redir.fd[0])
		close(mini->redir.fd[0]);
	while (mini->redir.str[i] == '<')
		i++;
	ft_memset(mini->redir.file, '\0', mini->redir.len);
	mini->redir.len = 0;
	while (mini->redir.str[i] == ' ')
		i++;
	i = cutfilename(mini, i, t, &mini->redir.file);
	redir_left_open(mini);
	return (i);
}

int	check_redir(char *str)
{
	int		i;
	char	dq;

	i = 0;
	if ((str[0] == '>' || str[0] == '<'))
		return (1);
	while (str[i])
	{
		if (str[i] < 0 && str[i] != -92)
		{
			dq = str[i++];
			while (str[i] != dq)
				i++;
		}
		else if ((str[i] == '>' || str[i] == '<') && str[i - 1] > 0)
			return (1);
		i++;
	}
	return (0);
}
