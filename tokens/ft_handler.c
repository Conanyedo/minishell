/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 09:07:44 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/19 15:02:55 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_redirec(t_mini *mini)
{
	int		len;
	t_redir redir;

	len = 0;
	mini->tmp = mini->cmd->pipe->content;
	redir = (t_redir) {0};
	if (!ft_strchr(mini->tmp, '>') && !ft_strchr(mini->tmp, '<'))
		return ;
	redir.str = ft_strdup(mini->tmp);
	free(mini->tmp);
	mini->tmp = (char*)malloc(sizeof(char) * ft_strlen(redir.str) + 1);
	while (redir.str[len] && redir.str[len] != '>' && redir.str[len] != '<')
		len++;
	ft_strlcpy(mini->tmp, redir.str, len + 1);
	if (ft_strchr(redir.str, '>') || ft_strchr(redir.str, '<'))
		redirect_right(mini, &redir);
	if (redir.start != 0)
	{
		if ((mini->tmp + redir.end)[0] != '\0')
			mini->tmp = ft_strjoin(mini->tmp, mini->tmp + redir.end);
		mini->fd = dup2(mini->fd, 1);
	}
	free(redir.str);
}
