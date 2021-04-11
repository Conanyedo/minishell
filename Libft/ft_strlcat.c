/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:30:17 by ybouddou          #+#    #+#             */
/*   Updated: 2019/11/05 16:39:56 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	if (!dst && size == 0)
		return (ft_strlen(src));
	while (dst[i] && i < size)
		i++;
	len = i;
	if (size == 0)
		return (ft_strlen(src));
	j = 0;
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (len < size)
		dst[i] = '\0';
	return (len + ft_strlen(src));
}
