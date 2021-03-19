/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:59:58 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/19 11:17:49 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_bdl_quot(t_mini *mini, int i)
{
	if (mini->check.quota)
		return ;
	if (mini->check.dbl_quota == 1)
		mini->check.dbl_quota = 0;
	else if (mini->check.dbl_quota == 0)
		mini->check.dbl_quota = 1;
	mini->input[i] *= -1;
}

void	check_one_quot(t_mini *mini, int i)
{
	if (mini->check.dbl_quota)
		return ;
	if (mini->check.quota == 1)
		mini->check.quota = 0;
	else if (mini->check.quota == 0)
		mini->check.quota = 1;
	mini->input[i] *= -1;
}
