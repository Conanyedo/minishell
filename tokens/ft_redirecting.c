/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirecting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:11:31 by cabouelw          #+#    #+#             */
/*   Updated: 2021/04/12 16:04:15 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	loop_redir(t_mini *mini, int i, int *idx, char t)
{
	while (mini->redir.str[i] && !mini->redir.err)
	{
		if (mini->redir.str[i] < 0 && mini->redir.str[i] != -92)
		{
			t = mini->redir.str[i];
			mini->redir.tmpstr[(*idx)++] = mini->redir.str[i++];
			while (mini->redir.str[i] && mini->redir.str[i] != t)
				mini->redir.tmpstr[(*idx)++] = mini->redir.str[i++];
			mini->redir.tmpstr[(*idx)++] = mini->redir.str[i++];
		}
		else if ((mini->redir.str[i] == '>' && !i) || (mini->redir.str[i] == '>' \
			&& mini->redir.str[i - 1] > 0))
			i = redir_right(mini, i, 0);
		else if ((mini->redir.str[i] == '<' && !i) || (mini->redir.str[i] == '<' \
			&& mini->redir.str[i - 1] > 0))
			i = redir_left(mini, i, 0);
		else if (mini->redir.str[i] == '1' && mini->redir.str[i - 1] == ' ' \
			&& mini->redir.str[i + 1] == '>')
			i++;
		else if (mini->redir.str[i] && mini->redir.str[i] > 1)
			mini->redir.tmpstr[(*idx)++] = mini->redir.str[i++];
		else
			i++;
	}
	return (*idx);
}

void	dup_in_out(t_mini *mini)
{
	if (mini->redir.fd[0])
		mini->fd[0] = mini->redir.fd[0];
	else
		mini->fd[0] = 0;
	if (mini->redir.fd[1])
	{
		mini->fd[1] = dup(mini->redir.fd[1]);
		close(mini->redir.fd[1]);
	}
	else
		mini->fd[1] = 0;
	if (mini->fd[0])
		dup2(mini->fd[0], 0);
	if (mini->fd[1])
		dup2(mini->fd[1], 1);
}

void	free_var(t_mini *mini)
{
	free(mini->redir.tmpstr);
	free(mini->redir.str);
	free(mini->redir.tmpfile);
	free(mini->redir.file);
}

void	redir(t_mini *mini, t_pipe **pipe, int i)
{
	int		idx;

	mini->redir = (t_redir){0};
	mini->fd[0] = 0;
	mini->fd[1] = 0;
	if (!check_redir((*pipe)->content))
		return ;
	mini->redir.str = ft_strdup((*pipe)->content);
	free((*pipe)->content);
	mini->redir.tmpstr = (char *)malloc(sizeof(char) * \
		ft_strlen(mini->redir.str));
	mini->redir.file = (char *)malloc(sizeof(char) * \
		ft_strlen(mini->redir.str));
	mini->redir.tmpfile = (char *)malloc(sizeof(char) * \
		ft_strlen(mini->redir.str));
	idx = 0;
	idx = loop_redir(mini, i, &idx, 0);
	mini->redir.tmpstr[idx] = '\0';
	(*pipe)->content = ft_strtrim(mini->redir.tmpstr, " \t");
	free_var(mini);
	if (mini->redir.err)
		return ;
	dup_in_out(mini);
}
