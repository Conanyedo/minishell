/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:59:58 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/27 18:38:59 by cabouelw         ###   ########.fr       */
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

char	check_slash(t_mini *mini, int i)
{
	if (mini->input[0] == '\\' && !mini->input[1])
	{
		ft_error_end("\\", mini);
		return (mini->input[0]);
	}
	if (!mini->input[i + 1])
	{
		error_newline(mini, i);
		return (0);
	}
	else if (mini->input[i + 1] && mini->input[i + 1] == '\\')
		return ('\\' * -1);
	else if (mini->input[i + 1] && mini->input[i + 1] == '$')
		return (1);
	else if (mini->check.dbl_quota)
	{
		if (mini->input[i + 1] == '"')
			return (mini->input[i] * -1);
		else
			return (mini->input[i]);
	}
	else if (mini->check.quota)
	{
		if (mini->input[i + 1] == '"')
			return (mini->input[i]);
		else if (mini->input[i + 1] == '\'')
			return (mini->input[i] * -1);
	}
	return (mini->input[i] * -1);
}

void	check_all(t_mini *mini, int i, int idx)
{
	if (i == 1)
	{
		if (mini->check.dbl_quota)
			ft_error_end("\"", mini);
		else if (mini->check.quota)
			ft_error_end("'", mini);
		if (mini->check.right || mini->check.left)
			error_symbols(mini, idx);
	}
	else
	{
		if (mini->check.left > 3 || mini->check.right > 2)
			error_symbols(mini, idx);
	}
}
