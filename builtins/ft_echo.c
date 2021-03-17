/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:49:02 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/17 14:48:55 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip(char *tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] > 0)
			ft_putchar_fd(tab[i], 1);
		i++;
	}
}

void	ft_echo(char **tab, int status)
{
	int		i;
	int		newline;

	i = 1;
	if (!tab[i] || !*tab[i])
		return (ft_putstr_fd("\n", 1));
	newline = ft_strncmp(tab[i], "-n", ft_strlen("-n"));
	if (!newline)
		i++;
	while (tab[i] && !ft_strncmp(tab[i], "-n", ft_strlen("-n")))
		i++;
	while (tab[i] && tab[i][0])
	{
		skip(tab[i]);
		if (tab[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline && !status)
		ft_putstr_fd("\n", 1);
}