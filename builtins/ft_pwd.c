/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:03:17 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/10 19:14:37 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_mini *mini)
{
	ft_putstr_fd(ft_lstsearch(mini->myenv, "PWD"), 1);
	ft_putstr_fd("\n", 1);
}