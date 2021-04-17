/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:27:05 by cabouelw          #+#    #+#             */
/*   Updated: 2021/04/17 14:10:16 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_symbols(t_mini *mini, int i)
{
	char	tmp;
	int		nb;

	nb = 0;
	while (mini->input[i] == ' ')
		i++;
	tmp = mini->input[i];
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	while (mini->input[i] == tmp && nb < 2)
	{
		nb++;
		if (!mini->input[i])
		{
			ft_putstr_fd("newline", 2);
			mini->status = 1;
			ft_putstr_fd("'\n", 2);
			return ;
		}
		ft_putchar_fd(mini->input[i++], 2);
	}
	ft_putstr_fd("'\n", 2);
	mini->status = 1;
}

void	error_arg(t_mini *mini)
{
	mini->cmd_status = 2;
	ft_putstr_fd("minishell: .: filename argument required\n", 2);
	ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
}

void	error_term(char *err)
{
	ft_putstr_fd(err, 2);
	exit (-1);
}

void	free_cmd(t_cmd	**cmd)
{
	t_cmd	*prev;

	prev = (*cmd);
	(*cmd) = (*cmd)->next;
	if (prev->content)
		free(prev->content);
	free(prev);
}

void	ambiguous(t_mini *mini, char *file)
{
	mini->cmd_status = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	free(mini->check.tmp);
	mini->check.tmp = NULL;
}
