/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 09:07:44 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/16 19:31:53 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	check_redirec(t_mini *mini)
{
	int		len;
	t_redir redir;

	len = 0;
	redir = (t_redir) {0};
	if (!ft_strchr(mini->cmd_list->pipe->content, '>') && !ft_strchr(mini->cmd_list->pipe->content, '<'))
		return ;
	redir.str = ft_strdup(mini->cmd_list->pipe->content);
	free(mini->cmd_list->pipe->content);
	mini->cmd_list->pipe->content = (char*)malloc(sizeof(char) * ft_strlen(redir.str) + 1);
	while (redir.str[len] && redir.str[len] != '>' && redir.str[len] != '<')
		len++;
	ft_strlcpy(mini->cmd_list->pipe->content, redir.str, len + 1);
	if (ft_strchr(redir.str, '>') || ft_strchr(redir.str, '<'))
		redirect_right(mini, &redir);
	if (redir.start != 0)
	{
		if ((mini->cmd_list->pipe->content + redir.end)[0] != '\0')
			mini->cmd_list->pipe->content = ft_strjoin(mini->cmd_list->pipe->content, mini->cmd_list->pipe->content + redir.end);
		mini->fd = dup2(mini->fd, 1);
	}
	free(redir.str);
}