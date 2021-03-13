/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:59:58 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/12 16:33:22 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_bdl_quot(t_mini *mini)//get value exmpl (echo "test;;;")
{
	if (mini->check.quota)
		return;
	if (mini->check.dbl_quota == 1)
		mini->check.dbl_quota = 0;
	else if (mini->check.dbl_quota == 0)
		mini->check.dbl_quota = 1;
}

void		check_one_quot(t_mini *mini)
{
	if (mini->check.dbl_quota)
		return;
	if (mini->check.quota == 1)
		mini->check.quota = 0;
	else if (mini->check.quota == 0)
		mini->check.quota = 1;
}