/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirecting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:11:31 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/27 11:41:53 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		redir_right_open(t_mini	*mini, int i)
{
	mini->redir.tmpfile[mini->redir.len] = '\0';
	stat(mini->redir.tmpfile, &mini->stt);
	// if (!(mini->stt.st_mode & X_OK))
	// {
	// 	permission(mini, mini->redir.tmpfile);
	// 	mini->redir.err = 1;
	// 	return (i);
	// }
	if (mini->redir.opn)
		mini->redir.fd[1] = open(mini->redir.tmpfile,\
			O_CREAT | O_RDWR | O_APPEND, 0666);
	else
		mini->redir.fd[1] = open(mini->redir.tmpfile,\
			O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (mini->redir.fd[1] < 0)
	{
		mini->redir.len = -1;
		error_file(mini, mini->redir.tmpfile, "");
		mini->redir.err = 1;
		return (i);
	}
	return (i);
}

int		redir_right(t_mini *mini, int i)
{
	(mini->redir.fd[1]) ? close(mini->redir.fd[1]) : (void)0;
	mini->redir.opn = (mini->redir.str[i + 1] == '>') ? 1 : 0;
	while (mini->redir.str[i] == '>')
		i++;
	ft_memset(mini->redir.tmpfile, '\0', mini->redir.len);
	mini->redir.len = 0;
	while (mini->redir.str[i] == ' ')
		i++;
	while (ft_isprint(mini->redir.str[i]) || mini->redir.str[i] < 0)
	{
		if (mini->redir.str[i] < 0)
		{
			i++;
			while (mini->redir.str[i] && mini->redir.str[i] > 0)
				mini->redir.tmpfile[mini->redir.len++] = mini->redir.str[i++];
			i++;
		}
		if (mini->redir.str[i] == '>' || mini->redir.str[i] == '<' || mini->redir.str[i] == ' ')
			break ;
		mini->redir.tmpfile[mini->redir.len++] = mini->redir.str[i++];
	}
	return (redir_right_open(mini, i));
}

int		redir_left(t_mini *mini, int i)
{
	(mini->redir.fd[0]) ? close(mini->redir.fd[0]) : (void)0;
	i++;
	ft_memset(mini->redir.file, '\0', mini->redir.len);
	mini->redir.len = 0;
	while (mini->redir.str[i] == ' ')
		i++;
	while (ft_isprint(mini->redir.str[i]) || mini->redir.str[i] < 0)
	{
		if (mini->redir.str[i] < 0)
		{
			i++;
			while (mini->redir.str[i] && mini->redir.str[i] > 0)
				mini->redir.file[mini->redir.len++] = mini->redir.str[i++];
			i++;
		}
		if (mini->redir.str[i] == '>' || mini->redir.str[i] == '<' || mini->redir.str[i] == ' ')
			break ;
		mini->redir.file[mini->redir.len++] = mini->redir.str[i++];
	}
	mini->redir.file[mini->redir.len] = '\0';
	mini->redir.fd[0] = open(mini->redir.file, O_RDONLY);
	if (mini->redir.fd[0] < 0)
	{
		mini->redir.len = -1;
		error_file(mini, mini->redir.file, "");
		mini->redir.err = 1;
		return (i);
	}
	return (i);
}

int		check_redir(char	*str)
{
	int		i;
	char	dq;

	i = 1;
	if ((str[0] == '>' || str[0] == '<'))
		return (1);
	while (str[i])
	{
		if (str[i] < 0 && str[i] != ('\\' * -1))
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

void	redir(t_mini *mini, t_pipe **pipe, int i)
{
	int		idx;

	mini->redir = (t_redir) {0};
	mini->redir.oldinput = dup(0);
	mini->redir.oldoutput = dup(1);
	mini->fd[0] = 0;
	mini->fd[1] = 0;
	if (!check_redir((*pipe)->content))
		return ;
	mini->redir.str = ft_strdup((*pipe)->content);
	free((*pipe)->content);
	mini->redir.tmpstr = (char*)malloc(sizeof(char) *\
		ft_strlen(mini->redir.str));
	mini->redir.file = (char*)malloc(sizeof(char) * ft_strlen(mini->redir.str));
	mini->redir.tmpfile = (char*)malloc(sizeof(char) *\
		ft_strlen(mini->redir.str));
	idx = i;
	while (mini->redir.str[i] && !mini->redir.err)
	{
		if (mini->redir.str[i] < 0 && mini->redir.str[i] != ('\\' * -1))
		{
			i++;
			while (mini->redir.str[i] && mini->redir.str[i] > 0)
				mini->redir.tmpstr[idx++] = mini->redir.str[i++];
			i++;
		}
		else if ((mini->redir.str[i] == '>' && !i) || (mini->redir.str[i] == '>' && mini->redir.str[i - 1] > 0))
			i = redir_right(mini, i);
		else if ((mini->redir.str[i] == '<' && !i) || (mini->redir.str[i] == '<' && mini->redir.str[i - 1] > 0))
			i = redir_left(mini, i);
		else if (mini->redir.str[i] == '1' && mini->redir.str[i + 1] == '>')
			i++;
		else if (mini->redir.str[i])
			mini->redir.tmpstr[idx++] = (mini->redir.str[i] > 0) ? mini->redir.str[i++] : idx--;
		else
			i++;
	}
	mini->redir.tmpstr[idx] = '\0';
	(*pipe)->content = ft_strtrim(mini->redir.tmpstr, " \t");
	free(mini->redir.tmpstr);
	if (mini->redir.err)
		return ;
	mini->fd[0] = (mini->redir.fd[0]) ? mini->redir.fd[0] : 0;
	mini->fd[1] = (mini->redir.fd[1]) ? mini->redir.fd[1] : 0;
	if (mini->fd[0])
		dup2(mini->fd[0], 0);
	if (mini->fd[1])
		dup2(mini->fd[1], 1);
}
