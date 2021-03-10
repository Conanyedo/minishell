/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:42:04 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/10 15:14:29 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		pipes_checker(char *s)
{
	int		i;
	int		p;

	i = 0;
	if (s[i] && s[i] == '|')
	{
		if (s[i + 1] && s[i + 1] =='|')
			return (2);
		else
			return (1);
	}
	while (s[i])//awddw|||
	{
		p = i;
		if (s[i] == '|' && !s[i + 1])
			return (1);
		if (s[i] == '|')
			while (s[p] && s[p] == '|')
				p++;
		if ((p - i) == 3 && s[p])
			return (1);
		else if ((p - i) > 3)
			return (2);
		i++;
	}
	return (0);
}


void	check_pipes(t_mini *mini)
{
	int		res;

	res = 0;
	if ((res = pipes_checker(mini->input)))
		error_pips(mini,res);
}