/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:49:02 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/19 12:34:32 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_mini *mini)
{
	int		i;
	int		newline;

	i = 1;
	if (!mini->tab[i] || !*mini->tab[i])
	{
		mini->cmd_status = 0;
		return (ft_putstr_fd("\n", 1));
	}
	newline = ft_strncmp(mini->tab[i], "-n", ft_strlen(mini->tab[i]));
	if (!newline)
		i++;
	while (mini->tab[i] && !ft_strncmp(mini->tab[i], "-n",
		ft_strlen(mini->tab[i])))
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
