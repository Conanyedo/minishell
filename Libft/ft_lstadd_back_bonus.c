/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 05:14:59 by ybouddou          #+#    #+#             */
/*   Updated: 2019/12/30 21:31:51 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (!new || !alst)
		return ;
	if (*alst)
	{
		last = *alst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*alst = new;
}
