/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirecting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:11:31 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/22 18:16:35 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		redir_right(t_mini *mini, int i)
{
	(mini->redir.fd[0]) ? close(mini->redir.fd[0]) : (void)0;
	mini->redir.opn = (mini->redir.str[i + 1] == '>') ? 1 : 0;
	while (mini->redir.str[i] == '>')
		i++;
	while (mini->redir.len > 0)
		mini->redir.tmpfile[mini->redir.len--] = '\0';
	while (mini->redir.str[i] == ' ')
		i++;
	while (ft_isalnum(mini->redir.str[i]) || mini->redir.str[i] < 0)
		(mini->redir.str[i] > 0) ? mini->redir.tmpfile[mini->redir.len++] =\
			mini->redir.str[i++] : i++;
	mini->redir.tmpfile[mini->redir.len] = '\0';
	if (mini->redir.opn)
		mini->redir.fd[0] = open(mini->redir.tmpfile,\
			O_CREAT | O_RDWR | O_APPEND, 0666);
	else
		mini->redir.fd[0] = open(mini->redir.tmpfile,\
			O_CREAT | O_RDWR | O_TRUNC, 0666);
	return (i);
}

int		redir_left(t_mini *mini, int i)
{
	(mini->redir.fd[1]) ? close(mini->redir.fd[1]) : (void)0;
	i++;
	while (mini->redir.len > 0)
		mini->redir.file[mini->redir.len--] = '\0';
	while (mini->redir.str[i] == ' ')
		i++;
	while (ft_isalnum(mini->redir.str[i]) || mini->redir.str[i] < 0)
		(mini->redir.str[i] > 0) ? mini->redir.file[mini->redir.len++] =\
			mini->redir.str[i++] : i++;
	mini->redir.file[mini->redir.len] = '\0';
	mini->redir.fd[1] = open(mini->redir.file, O_RDONLY);
	if (mini->redir.fd[1] < 0)
	{
		mini->redir.len = -1;
		error_file(mini, mini->redir.file, "");
		return (i);
	}
	return (i);
}

void	redir(t_mini *mini, int i)
{
	int		idx;

	mini->redir = (t_redir) {0};
	if (!ft_strchr(mini->cmd->pipe->content, '>') &&\
		!ft_strchr(mini->cmd->pipe->content, '<'))
		return ;
	mini->redir.str = mini->cmd->pipe->content;
	mini->redir.tmpstr = (char*)malloc(sizeof(char) *\
		ft_strlen(mini->redir.str));
	mini->redir.file = (char*)malloc(sizeof(char) * ft_strlen(mini->redir.str));
	mini->redir.tmpfile = (char*)malloc(sizeof(char) *\
		ft_strlen(mini->redir.str));
	idx = i;
	while (mini->redir.str[i] && !mini->cmd_status)
		if (mini->redir.str[i] == '>')
			i = redir_right(mini, i);
		else if (mini->redir.str[i] == '<')
			i = redir_left(mini, i);
		else
			mini->redir.tmpstr[idx++] = mini->redir.str[i++];
	mini->redir.tmpstr[idx] = '\0';
	free(mini->cmd->pipe->content);
	mini->cmd->pipe->content = mini->redir.tmpstr;
	mini->fd[0] = mini->redir.fd[0];
	mini->fd[1] = mini->redir.fd[1];
}
