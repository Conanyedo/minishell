/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplittools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:29:49 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/19 17:32:21 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		exist(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	loop(char **s, char *token, int *dq, char *q)
{
	while (**s && !exist(token, **s) && *dq == 0)
	{
		if (**s < 0 && **s != -92)
		{
			*q = **s;
			*dq = 1;
		}
		else
			(*s)++;
	}
}

void	skipping(char **s, char *token, int *words, char *q)
{
	int		dq;

	dq = 0;
	loop(s, token, &dq, q);
	if (exist(token, **s) && !dq)
	{
		*words = *words + 1;
		while (**s && exist(token, **s))
			(*s)++;
	}
	else if (**s && **s == *q && dq == 1)
	{
		(*s)++;
		while (**s && **s != *q)
			(*s)++;
		dq = 0;
		(*s)++;
	}
	*words = (!**s && !exist(token, *(*s - 1))) ? (*words + 1) : *words;
}
