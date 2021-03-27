/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:42:04 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/27 11:03:27 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_pipes(t_mini *mini, int i)
{
	if (mini->check.dbl_quota || mini->check.quota)
		return ;
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
