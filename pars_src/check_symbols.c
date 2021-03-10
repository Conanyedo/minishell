/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:15:17 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/09 15:37:59 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		if_error_symbols(char *s)
{
	int		i;
	int		check;

	i = 0;
	check = 0;
	while (s[i] && s[i] != '"' && s[i] != '\'')
	{
		if (s[i] == '>' || s[i] == '<')
		{
			check = 1;
			if (s[i + 1] == '>' || s[i + 1] == '<')
			{
				check = 2;
				i += 2;
			}
			while (s[i] == ' ')
				i++;
			if (!s[i] || !ft_isalpha(s[i]) || !ft_isdigit(s[i]))
				return (1);
			else
				break;
		}
		i++;
	}
	return (0);
}

void	check_symbols(t_mini *mini)
{
	if (if_error_symbols(mini->input))
		error_newline(mini);
	
}