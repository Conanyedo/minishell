/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 21:23:14 by ybouddou          #+#    #+#             */
/*   Updated: 2019/12/31 00:54:36 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

void f(void *b)
{
	char *a = b;
	*a = *a + 1;
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *tmp;

	if (!lst || !f)
		return ;
	tmp = lst;
	while (tmp)
	{
		f(tmp->content);
		tmp = tmp->next;
	}
}

int main()
{
	t_list **pp;
	t_list *node1;
	t_list *node2;

	node1 = ft_lstnew(ft_strdup("a"));
	node2 = ft_lstnew(ft_strdup("b"));
	ft_lstadd_back(pp, node1);
	ft_lstadd_back(pp, node2);
	ft_lstiter(node1, f);
	while (*pp)
	{
		printf("%s\n", (*pp)->content);
		(*pp) = (*pp)->next;		
	}
	return (0);
}
