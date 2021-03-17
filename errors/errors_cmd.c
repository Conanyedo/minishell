/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:36:19 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/16 19:04:17 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_not_found(t_mini *mini)
{
	mini->status = 127;
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(mini->tab[0], 1);
	ft_putstr_fd(": command not found\n", 1);
}


void	error_file(char	*file, t_mini *mini)
{
	// mini->status = 1;
	(void)mini;
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(file, 1);
	ft_putstr_fd(": No such file or directory\n", 1);
}