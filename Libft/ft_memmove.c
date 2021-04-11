/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:24:18 by ybouddou          #+#    #+#             */
/*   Updated: 2019/11/08 22:54:36 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (dst == src)
		return (dst);
	i = -1;
	if (!dst && !src)
		return (0);
	if (s < d)
		while (len--)
			d[len] = s[len];
	else
		while (++i < len)
			d[i] = s[i];
	return (dst);
}
