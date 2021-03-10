/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:49:02 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/09 15:35:57 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char **str)
{
	int		i;

	i = 1;
	if (str[i] && !(ft_strncmp(str[i], "-n", ft_strlen(str[i]))))
		i++;
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		if (str[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (str[1] && (ft_strncmp(str[1], "-n", ft_strlen(str[1]))))
		ft_putstr_fd("\n", 1);
}