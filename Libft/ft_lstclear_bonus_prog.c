/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 21:21:52 by ybouddou          #+#    #+#             */
/*   Updated: 2019/12/30 23:35:17 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

void del (void *a)
{
	    a = 0;
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}

/*int main()
{
	t_list **pp;
	t_list *node1;
	t_list *node2;

	node1 = ft_lstnew("hello");
	node2 = ft_lstnew("world");
	ft_lstadd_back(pp, node1);
	ft_lstadd_back(pp, node2);
	printf("%s\n", (*pp)->content);
	ft_lstclear(pp, del);
	printf("%s\n", (*pp)->content);
	while (*pp)
	{
		printf("%s\n", (*pp)->content);
		(*pp) = (*pp)->next;
	}
	return (0);
}*/
