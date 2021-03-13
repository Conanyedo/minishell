/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 12:36:19 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/11 17:21:38 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void cmd_not_found(t_mini *mini)
{
	mini->status = 1;
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(mini->tab[0], 1);
	ft_putstr_fd(": command not found\n", 1);
}