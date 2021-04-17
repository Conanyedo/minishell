/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 17:52:41 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/17 13:52:01 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(t_mini *mini, t_read *s_read, t_history **list)
{
	t_history	*node;

	ft_putstr_fd("\n", 1);
	mini->cmd_status = 1;
	delete_node(&mini->hist);
	create_node(&node, 1);
	(*list) = add_node(&mini->hist, node);
	prompt(mini);
	get_cursor(s_read, list);
}

void	ctrl_d(t_history **list)
{
	if ((*list)->tmp)
		return ;
	ft_putstr_fd("exit\n", 1);
	delete_node(&g_mini->hist);
	exit (g_mini->cmd_status);
}

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	g_mini->cmd_status = 130;
}

void	handle_sigquit(int sig)
{
	(void)sig;
	g_mini->cmd_status = 131;
	if (g_mini->pid)
		ft_putstr_fd("Quit: 3\n", 1);
}
