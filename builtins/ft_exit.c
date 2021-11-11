/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:03:10 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/18 12:52:48 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	checkfirst(t_mini *mini, int *i)
{
	if (ft_atoi(mini->tabu[1]) < 0)
	{
		ft_putstr_fd("exit\nminishell: exit: ", 1);
		ft_putstr_fd(mini->tabu[1], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit(255);
	}
	while (mini->tabu[1] && mini->tabu[1][*i])
	{
		if (!ft_isdigit(mini->tabu[1][*i]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 1);
			ft_putstr_fd(mini->tabu[1], 1);
			ft_putstr_fd(": numeric argument required\n", 1);
			exit(1);
		}
		(*i)++;
	}
}

void	ft_exit(t_mini *mini)
{
	int		i;

	i = 0;
	if (!mini->tabu[1])
	{
		ft_putstr_fd("exit\n", 1);
		exit(mini->cmd_status);
	}
	if (mini->tabu[1] && (mini->tabu[1][i] == '+' || mini->tabu[1][i] == '-'))
		i++;
	checkfirst(mini, &i);
	if (mini->tabu[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 1);
		mini->cmd_status = 1;
		return ;
	}
	ft_putstr_fd("exit\n", 1);
	if (mini->tabu[1] && mini->tabu[1][0] && ft_atoi(mini->tabu[1]))
		exit(ft_atoi(mini->tabu[1]));
	mini->cmd_status = 0;
	exit(mini->cmd_status);
}
