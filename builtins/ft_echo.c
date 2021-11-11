/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:49:02 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/18 13:22:08 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	option(char *tabu, int *nl)
{
	int		i;

	i = 1;
	if (!tabu[i])
		return (0);
	while (tabu[i] && tabu[i] == 'n')
		i++;
	if (tabu[i])
		return (0);
	*nl = 0;
	return (1);
}

void	ft_echo(t_mini *mini)
{
	int		i;
	int		nl;

	i = 1;
	nl = 1;
	if (!mini->tabu[i] || !*mini->tabu[i])
	{
		mini->cmd_status = 0;
		return (ft_putstr_fd("\n", 1));
	}
	while (mini->tabu[i] && *mini->tabu[i] == '-' && option(mini->tabu[i], &nl))
		i++;
	while (mini->tabu[i])
	{
		ft_putstr_fd(mini->tabu[i], 1);
		if (mini->tabu[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (nl)
		ft_putstr_fd("\n", 1);
	mini->cmd_status = 0;
}
