/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:51:47 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/14 15:26:36 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env *env)
{
	t_env	*list;

	list = env;
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
}