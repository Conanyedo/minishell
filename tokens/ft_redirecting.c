/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirecting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:11:31 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/16 19:30:53 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_files(t_mini *mini, t_redir *redir, int status)
{
	int		len;

	if (mini->fd > 1)
		close(mini->fd);
	if (redir->start == 0)
		redir->start = redir->i;
	redir->i += status;
	while (redir->str[redir->i] == ' ')
		redir->i++;
	len = 0;
	while (redir->str[redir->i] && redir->str[redir->i] != ' ' &&\
		redir->str[redir->i] != '>' && redir->str[redir->i] != '<')
	{
		redir->i++;
		len++;
	}
	redir->tmpfile = (char*)malloc(sizeof(char) * len + 1);
	ft_strlcpy(redir->tmpfile, redir->str + (redir->i - len), len + 1);
	if (status == 1)
		mini->fd = open(redir->tmpfile, O_CREAT | O_WRONLY, 0666);
	else if (status == 2)
		mini->fd = open(redir->tmpfile,O_CREAT | O_RDWR | O_APPEND, 0666);
	redir->end = redir->i;
	redir->i--;
}

void case_left(t_redir *redir)
{
	int		len;
	int		start;

	len = 0;
	redir->i++;
	while (redir->str[redir->i] == ' ')
		redir->i++;
	start = redir->i;
	while (redir->str[redir->i] && redir->str[redir->i] != ' ' && redir->str[redir->i] != redir->dp)
	{
		redir->i++;
		len++;
	}
	redir->file = ft_substr(redir->str, start, len + 1);
	redir->file = ft_strjoin(" ", redir->file);
}

void	redirect_right(t_mini *mini, t_redir *redir)
{
	while (redir->str[redir->i])
	{
		if (redir->str[redir->i] && (redir->str[redir->i] == '"' || redir->str[redir->i] == '\''))
		{
			redir->dp = redir->str[redir->i++];
			while (redir->str[redir->i] && redir->str[redir->i] != redir->dp)
				redir->i++;
		}
		else if (redir->str[redir->i + 1] && redir->str[redir->i] == '>'\
			&& redir->str[redir->i + 1] != '>')
			open_files(mini, redir, 1);
		else if (redir->str[redir->i + 1] && redir->str[redir->i] == '>'\
			&& redir->str[redir->i + 1] == '>')
			open_files(mini, redir, 2);
		else if (redir->str[redir->i] == '<')
			case_left(redir);
		redir->i++;
	}
	if (redir->file)
		mini->cmd_list->pipe->content = ft_strjoin(mini->cmd_list->pipe->content, redir->file);
	if (mini->fd < 0)
		error_file(redir->tmpfile, mini);
}