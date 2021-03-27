/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:42:04 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/25 11:57:17 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_pipes(t_mini *mini, int i)
{
	if (mini->check.dbl_quota || mini->check.quota)
		return ;
	if (i == 0)
	{
		if (mini->input[i + 1] && mini->input[i + 1] == '|')
			error_pips(mini, 2);
		else
			error_pips(mini, 1);
	}
	else if (mini->check.pipe && mini->input[i + 1] == '|')
		error_pips(mini, 2);
	else if (mini->check.pipe || (!mini->input[i + 1]))
		error_pips(mini, 1);
	else if (mini->check.pipe == 0)
		mini->check.pipe = 1;
}

void	if_isdirect(t_mini *mini, char *s)
{
	int		i;
	int		point;

	i = 0;
	while (s[i] == '.')
		i++;
	if (i == 1 && !s[i])
		return (error_arg(mini));
	if (i && (!s[i] || s[i] != '/'))
		return (cmd_not_found(mini));
	while (s[i] == '/' || s[i] == '.')
	{
		point = 0;
		while (s[i] == '.')
		{
			if (point > 1)
				return (error_file(mini, s, ""));
			point++;
			i++;
		}
		i++;
	}
	if (!s[i])
		return (is_directory(mini));
	mini->check.point = 0;
}
