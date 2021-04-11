/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:06:47 by ybouddou          #+#    #+#             */
/*   Updated: 2019/11/09 16:01:13 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = 0;
	if (!*to_find)
		return ((char *)str);
	if ((!str || !to_find) && n == 0)
		return (NULL);
	while (to_find[len])
		len++;
	while (str[i])
	{
		while (str[i + j] == to_find[j] && (i + j) < n)
		{
			if (j == len - 1)
				return ((char *)str + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
