/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirecting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:11:31 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/27 12:06:14 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	loop_redir(t_mini *mini, int i, int idx)
{
	while (mini->redir.str[i] && !mini->redir.err)
	{
		if (mini->redir.str[i] < 0 && mini->redir.str[i] != ('\\' * -1))
		{
			i++;
			while (mini->redir.str[i] && mini->redir.str[i] > 0)
				mini->redir.tmpstr[idx++] = mini->redir.str[i++];
			i++;
		}
		else if ((mini->redir.str[i] == '>' && !i) || (mini->redir.str[i] == '>'
			&& mini->redir.str[i - 1] > 0))
			i = redir_right(mini, i);
		else if ((mini->redir.str[i] == '<' && !i) || (mini->redir.str[i] == '<'
			&& mini->redir.str[i - 1] > 0))
			i = redir_left(mini, i);
		else if (mini->redir.str[i] == '1' && mini->redir.str[i + 1] == '>')
			i++;
		else if (mini->redir.str[i])
			mini->redir.tmpstr[idx++] = (mini->redir.str[i] > 0) ?
				mini->redir.str[i++] : idx--;
		else
			i++;
	}
	mini->redir.tmpstr[idx] = '\0';
}

void	redir(t_mini *mini, t_pipe **pipe, int i)
{
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
	loop_redir(mini, i, i);
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
