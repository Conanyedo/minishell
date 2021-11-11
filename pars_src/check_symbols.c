/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:15:17 by cabouelw          #+#    #+#             */
/*   Updated: 2021/04/12 13:40:39 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_symbols(t_mini *mini, int i)
{
	if (mini->status || mini->check.quota || mini->check.dbl_quota)
		return ;
	if (mini->check.symbols == 0)
		mini->check.symbols = mini->input[i];
	else if (mini->check.symbols != mini->input[i])
		error_symbols(mini, i);
	else if (mini->input[i - 1] == ' ' && \
		(mini->check.left || mini->check.right))
		error_symbols(mini, i);
	if ((mini->check.left > 2 || mini->check.right > 1) && !mini->status)
		error_symbols(mini, i);
	if (mini->input[i] == '>')
		mini->check.right++;
	else
		mini->check.left++;
}
