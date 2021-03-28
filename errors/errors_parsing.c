/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:27:05 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/28 16:46:04 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error_end(char *s, t_mini *mini)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'\n", 2);
	mini->status = 1;
	mini->check.point = 0;
}

void	error_newline(t_mini *mini, int i)
{
	(void)i;
	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n"
		, 2);
	mini->status = 1;
}

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

void	error_pips(t_mini *mini, int res)
{
	if (res >= 2)
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
	else if (res == 1)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	mini->status = 1;
	mini->check.pipe = 0;
}

void	error_arg(t_mini *mini)
{
	mini->cmd_status = 2;
	ft_putstr_fd("minishell: .: filename argument required\n", 2);
	ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
}
