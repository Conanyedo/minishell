/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:51:47 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/19 12:34:42 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_mini *mini)
{
	t_env	*list;

	if (mini->tab[1])
	{
		error_file(mini, mini->tab[1], "env");
		return ;
	}
	list = mini->myenv;
	while (list)
	{
		if (*list->symbol)
		{
			ft_putstr_fd(list->key, 1);
			ft_putstr_fd(list->symbol, 1);
			ft_putstr_fd(list->value, 1);
			ft_putstr_fd("\n", 1);
		}
		list = list->next;
	}
	mini->cmd_status = 0;
}
