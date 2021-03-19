/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:03:10 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/19 12:53:35 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	checkfirst(t_mini *mini, int *i)
{
	while (mini->tab[1] && mini->tab[1][*i])
	{
		if (!ft_isdigit(mini->tab[1][*i]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 1);
			ft_putstr_fd(mini->tab[1], 1);
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
	if (!mini->tab[1])
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	if (mini->tab[1] && (mini->tab[1][i] == '+' || mini->tab[1][i] == '-'))
		i++;
	checkfirst(mini, &i);
	if (mini->tab[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 1);
		mini->cmd_status = 1;
		return ;
	}
	ft_putstr_fd("exit\n", 1);
	if (mini->tab[1] && mini->tab[1][0] && ft_atoi(mini->tab[1]))
		exit(ft_atoi(mini->tab[1]));
	mini->cmd_status = 0;
	exit(0);
}
