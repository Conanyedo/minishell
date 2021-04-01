/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:49:02 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/30 10:47:09 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		option(char *tab, int *newline)
{
	int		i;

	i = 1;
	if (!tab[i])
		return (0);
	while (tab[i] && tab[i] == 'n')
		i++;
	if (tab[i])
		return (0);
	*newline = 0;
	return (1);
}

void	ft_echo(t_mini *mini)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;
	if (!mini->tab[i] || !*mini->tab[i])
	{
		mini->cmd_status = 0;
		return (ft_putstr_fd("\n", 1));
	}
	while (*mini->tab[i] == '-' && option(mini->tab[i], &newline))
		i++;
	while (mini->tab[i])
	{
		ft_putstr_fd(mini->tab[i], 1);
		if (mini->tab[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	mini->cmd_status = 0;
}
