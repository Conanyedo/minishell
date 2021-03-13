/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:15:17 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/13 10:34:22 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_symbols(t_mini *mini,int i)
{
	if (mini->check.symbols == 0)
		mini->check.symbols = mini->input[i];
	if (mini->check.symbols == '>' && mini->input[i] == '<')
		error_symbols(mini, i);
	else if (mini->check.left > 3 && mini->check.right > 2)
		error_symbols(mini, i);
	else if (mini->input[i - 1] && mini->input[i - 1] == ' ' &&\
		(mini->check.left || mini->check.right))
		error_symbols(mini, i);
	else if (mini->check.symbols == '>')
		mini->check.right++;
	else if (mini->check.symbols == '<')
		mini->check.left++;
	else if (mini->check.left > 3 || mini->check.right > 2)
		error_symbols(mini, i);
}