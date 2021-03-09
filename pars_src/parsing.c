/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:55:23 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/08 17:58:19 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse(t_mini *mini)
{
    int i;

    i = 0;
	ft_separate(mini);
    if (ft_strchr(mini->input,'<') || ft_strchr(mini->input,'>'))
        check_symbols(mini);
    while (mini->input[i])
    {
        i++;
    }
	// if (mini->check.value != '\0')
		// printf("{%s}\n",mini->check.err);
	// mini->path_value = ft_lstsearch(mini->myenv, "PATH");
	// mini->paths = ft_split(mini->path_value, ':');
}
