/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 00:20:41 by ybouddou          #+#    #+#             */
/*   Updated: 2019/12/31 00:32:44 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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

int		main()
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

	while(result)
	{
		printf("%s\n", result -> content);
		result = result -> next;
	}
}
