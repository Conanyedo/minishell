/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:42:04 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/12 15:37:13 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_pipes(t_mini *mini, int i)
{
	if (mini->check.dbl_quota || mini->check.quota)
		return;
	if (i == 0)
	{
		if (mini->input[i + 1] && mini->input[i + 1] == '|')
			error_pips(mini, 2);
		else
			error_pips(mini, 1);
	}
	else if (mini->check.pipe && mini->input[i + 1] == '|')
		error_pips(mini, 2);
	else if (mini->check.pipe || (!mini->input[i + 1]))
		error_pips(mini, 1);
	else if (mini->check.pipe == 0)
		mini->check.pipe = 1;
}