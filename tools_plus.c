/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:39:04 by cabouelw          #+#    #+#             */
/*   Updated: 2021/04/03 14:40:41 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_mini *mini)
{
	if (mini->fd[1])
	{
		close(mini->fd[1]);
		mini->fd[1] = 0;
	}
	if (mini->fd[0])
	{
		close(mini->fd[0]);
		mini->fd[0] = 0;
	}
}
