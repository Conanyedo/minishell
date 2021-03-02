/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 21:24:19 by ybouddou          #+#    #+#             */
/*   Updated: 2019/12/30 23:38:33 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

void *func1(void *a)
{
	char *s = ft_strdup(a);
	*s = *s + 1;
	return ((void *)s);
}

void del (void *a)
{
	a = 0;
}


t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *head;
	t_list *new;

	if (!lst || !f || !del)
		return (NULL);
	head = ft_lstnew(f(lst->content));
	lst = lst->next;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}


int main(void)
{
	t_list *test;
	t_list *test2;
	t_list *test3;
	t_list *result;

	test = ft_lstnew(ft_strdup("a"));
	test2 = ft_lstnew(ft_strdup("b"));
	test3 = ft_lstnew(ft_strdup("c"));

	ft_lstadd_back(&test, test2);
	ft_lstadd_back(&test, test3);

	result = ft_lstmap(test, &func1, &del);

	while(result){
		printf("%s\n", result -> content);
		result = result -> next;
	}
}
