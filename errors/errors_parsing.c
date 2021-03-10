/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:27:05 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/10 19:21:09 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_error_end(char *s, t_mini *mini) // error return
{
	printf("minishell: syntax error near unexpected token `%s'\n",s);
	mini->status = 1;
}
void error_newline(t_mini *mini) // error newlin >> << > < ...
{
	printf("minishell: syntax error near unexpected token `newline'\n");
	mini->status = 1;
}

void	error_symbols_left(t_mini *mini, int nb)
{
	if (nb == 3)
		printf("minishell: syntax error near unexpected token `%c'\n",\
			mini->check.symbols);
	else if (mini->check.symbols != '<')
		printf("minishell: syntax error near unexpected token `%c%c'\n",\
			mini->check.symbols, mini->check.symbols);
	else if (mini->check.symbols == '<' && nb < 5)
		printf("minishell: syntax error near unexpected token `%c'\n",mini->check.symbols);
	else if (mini->check.symbols == '<')
		printf("minishell: syntax error near unexpected token `%c%c'\n",\
			mini->check.symbols, mini->check.symbols);
	mini->status = 1;
}

void error_pips(t_mini *mini, int res)
{
	if (res >= 2)
		printf("minishell: syntax error near unexpected token `||'\n");
	else if (res == 1)
		printf("minishell: syntax error near unexpected token `|'\n");
	mini->status = 1;
}