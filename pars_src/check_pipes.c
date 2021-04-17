/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:42:04 by cabouelw          #+#    #+#             */
/*   Updated: 2021/04/17 13:59:22 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_pipes(t_mini *mini, int i)
{
	if (mini->check.dbl_quota || mini->check.quota)
		return ;
	if (mini->check.right || mini->check.left ||\
		mini->check.pipe || !mini->input[i + 1])
		error_symbols(mini, i);
	else if (mini->check.pipe == 0)
		mini->check.pipe = 1;
}

void	prepare_pipes(t_mini *mini, int pipes)
{
	mini->pidpipe = (int *)malloc(sizeof(int) * (pipes + 1));
	mini->pipefds = (int *)malloc(sizeof(int) * (pipes * 2));
	mini->index = -1;
	while (++mini->index < pipes)
		pipe(mini->pipefds + (mini->index * 2));
	mini->index = 0;
	mini->p = 0;
}

void	close_pipes(t_mini *mini, int pipes)
{
	mini->index = -1;
	while (++mini->index < (pipes * 2))
		close(mini->pipefds[mini->index]);
	mini->index = -1;
	while (++mini->index <= pipes && pipes)
	{
		waitpid(mini->pidpipe[+mini->index], &mini->r, 0);
		mini->cmd_status = WEXITSTATUS(mini->r);
	}
	free(mini->pipefds);
	free(mini->pidpipe);
}
