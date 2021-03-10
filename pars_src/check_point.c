/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:46:50 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/10 11:36:22 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	end_cmd_check(t_mini *mini, int  i) // check if ';;' double in the same line
{

	while (mini->input[i])
	{
		if (mini->status)
			break;
		if (mini->input[i] == ';')
		{
			(mini->input[i + 1] == ';') ? ft_error_end(";;", mini) : (mini->check.end = 1);
			(mini->input[i + 1] != ';' && mini->input[i + 1] && mini->input[i + 1] != ' ') ? (mini->check.end = 0) : (void)0;
			i++;
		}
		while (mini->input[i] == ' ')
			i++;
		(mini->input[i] == ';' && mini->check.end == 1) ? ft_error_end(";", mini) : (mini->check.end = 0);
		if (mini->input[i] == '"')
			i = check_bdl_quot(mini,i);
		else if (mini->input[i] == '\'')
			i = check_one_quot(mini,i);
		else
			i++;
	}
}

void	ft_checkpoints(t_mini *mini)
{
	int i;

	i = 0;i = 0;
	if (mini->input[i] == ';')
	{
		if (mini->input[i + 1] == ';')
			ft_error_end(";;", mini);
		else
			ft_error_end(";", mini);
	}
	end_cmd_check(mini, i);
}
