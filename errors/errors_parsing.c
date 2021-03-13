/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:27:05 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/13 14:39:17 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_error_end(char *s, t_mini *mini) // error return
{
	printf("minishell: syntax error near unexpected token `%s'\n",s);
	mini->status = 1;
	mini->check.point = 0;
}

void error_newline(t_mini *mini, int i) // error newlin >> << > < ...
{
	(void)i;
	printf("minishell: syntax error near unexpected token `newline'\n");
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
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	while (mini->input[i] == tmp && nb < 2)
	{
		nb++;
		if (!mini->input[i])
		{
			ft_putstr_fd("newline", 1);
			mini->status = 1;
			ft_putstr_fd("'\n", 1);
			return;
		}
		ft_putchar_fd(mini->input[i++], 1);
	}
	ft_putstr_fd("'\n", 1);
	mini->status = 1;
}

void error_pips(t_mini *mini, int res)
{
	if (res >= 2)
		printf("minishell: syntax error near unexpected token `||'\n");
	else if (res == 1)
		printf("minishell: syntax error near unexpected token `|'\n");
	mini->status = 1;
	mini->check.pipe = 0;
}