/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:27:05 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/08 17:44:33 by cabouelw         ###   ########.fr       */
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