/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:59:58 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/11 11:01:10 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_bdl_quot(t_mini *mini, int i)//get value exmpl (echo "test;;;")
{
	int pos;

	pos = i + 1;
	while (mini->input[pos] != '"' && mini->input[pos])
		pos++;
	if (mini->input[pos] == '"')
		mini->check.value = ft_substr(mini->input, i + 1, pos - i - 1);
	else
		mini->status = 1;
	return (pos + 1);
}

int		check_one_quot(t_mini *mini, int i)
{
	int pos;

	pos = i + 1;
	while (mini->input[pos] != '\'' && mini->input[pos])
		pos++;
	if (mini->input[pos] == '\'')
		mini->check.value = ft_substr(mini->input, i + 1, pos - i - 1);
	else
		mini->status = 1;
	return (pos + 1);
}