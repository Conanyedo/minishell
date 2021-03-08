/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:55:23 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/08 17:06:26 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse(t_mini *mini)
{
	ft_separate(mini);
	// if (mini->check.value != '\0')
		// printf("{%s}\n",mini->check.err);
	// mini->path_value = ft_lstsearch(mini->myenv, "PATH");
	// mini->paths = ft_split(mini->path_value, ':');
}
