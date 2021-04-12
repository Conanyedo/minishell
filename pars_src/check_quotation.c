/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:59:58 by cabouelw          #+#    #+#             */
/*   Updated: 2021/04/12 13:40:26 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_bdl_quot(t_mini *mini, int i)
{
	if (mini->check.quota)
		return ;
	if (mini->check.dbl_quota == 1)
		mini->check.dbl_quota = 0;
	else
		mini->check.dbl_quota = 1;
	mini->input[i] *= -1;
}

void	check_one_quot(t_mini *mini, int i)
{
	if (mini->check.dbl_quota)
		return ;
	if (mini->check.quota == 1)
		mini->check.quota = 0;
	else
		mini->check.quota = 1;
	mini->input[i] *= -1;
}

char	check_slash(t_mini *mini, int i)
{
	if (!mini->input[i + 1])
		error_symbols(mini, i);
	else if (mini->input[i + 1] == '\\')
		return ('\\' * -1);
	else if (mini->input[i + 1] == '$')
		return (1);
	else if (mini->check.dbl_quota && mini->input[i + 1] != '"')
		return (mini->input[i]);
	else if (mini->check.quota)
		if (mini->input[i + 1] == '"')
			return (mini->input[i]);
	return (mini->input[i] * -1);
}

void	check_all(t_mini *mini, int i, int idx)
{
	if (i == 1)
	{
		if (mini->check.dbl_quota || mini->check.quota || \
			mini->check.right || mini->check.left || mini->check.pipe)
			error_symbols(mini, idx);
	}
	else
		if (mini->check.left > 3 || mini->check.right > 2)
			error_symbols(mini, idx);
}
