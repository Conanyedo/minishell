/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:03:17 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/27 14:28:55 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_mini *mini)
{
	char	cwd[1028];

	getcwd(cwd, 1028);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	mini->cmd_status = 0;
}
