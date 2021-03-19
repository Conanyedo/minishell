/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:46:50 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/19 11:17:10 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	end_cmd_check(t_mini *mini, int i)
{
	if (mini->status || mini->check.quota || mini->check.dbl_quota)
		return ;
	if (mini->check.left != 0 || mini->check.right != 0)
	{
		if (mini->input[i + 1] && mini->input[i + 1] == ';')
			ft_error_end(";;", mini);
		else
			ft_error_end(";", mini);
	}
	if (mini->input[i] == ';' && mini->check.point == 0)
		mini->check.point = 1;
	else if (mini->input[i] == ';' && mini->input[i + 1] == ';'
		&& mini->check.point == 1)
		ft_error_end(";;", mini);
	else if (mini->input[i] == ';' && mini->input[i - 1] == ';'
		&& mini->check.point == 1)
		ft_error_end(";;", mini);
	else if (mini->input[i] == ';' && mini->check.point == 1)
		ft_error_end(";", mini);
}

void	check_point(t_mini *mini, int i)
{
	if (mini->input[i] == ';' && i == 0)
	{
		if (mini->input[i + 1] == ';')
			ft_error_end(";;", mini);
		else
			ft_error_end(";", mini);
	}
	end_cmd_check(mini, i);
}
