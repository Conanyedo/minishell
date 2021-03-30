/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:42:04 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/29 19:53:53 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_pipes(t_mini *mini, int i)
{
	if (mini->check.dbl_quota || mini->check.quota)
		return ;
	if ((mini->check.right || mini->check.left) ||\
		(mini->check.pipe || !mini->input[i + 1]))
		error_symbols(mini, i);
	else if (mini->check.pipe == 0)
		mini->check.pipe = 1;
}
