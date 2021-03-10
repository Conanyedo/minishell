/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:49:02 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/10 19:21:37 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char **tab)
{
	int		i;

	i = 0;
	tab++;
	if (tab[i] && !(ft_strncmp(tab[i], "-n", ft_strlen(tab[i]))))
		tab++;
	while (tab[i])
	{
		tab[i] = ft_strtrim(tab[i], "\"\'");
		ft_putstr_fd(tab[i], 1);
		if (tab[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (tab[1] && (ft_strncmp(tab[1], "-n", ft_strlen(tab[1]))))
		ft_putstr_fd("\n", 1);
}