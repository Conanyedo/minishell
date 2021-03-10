/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:51:47 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/09 15:12:53 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_env *env)
{
	t_env	*fresh;

	fresh = env;
	while (fresh)
	{
		ft_putstr_fd(fresh->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(fresh->value, 1);
		ft_putstr_fd("\n", 1);
		fresh = fresh->next;
	}
}