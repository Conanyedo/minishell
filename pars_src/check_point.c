/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:46:50 by cabouelw          #+#    #+#             */
/*   Updated: 2021/04/12 13:40:19 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_point(t_mini *mini, int i)
{
	if (mini->status || mini->check.quota || mini->check.dbl_quota)
		return ;
	if (mini->check.left != 0 || mini->check.right != 0 || \
		mini->check.point || mini->input[i + 1] == ';')
		error_symbols(mini, i);
	else if (mini->check.point == 0)
		mini->check.point = 1;
}
