/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 17:15:17 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/10 19:30:09 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//bash-3.2$ echo > <
// bash: syntax error near unexpected token `<'
// bash-3.2$ > > > >
// bash: syntax error near unexpected token `>'
// bash-3.2$ >> >> >> >>
// bash: syntax error near unexpected token `>>'
int		if_error_symbols(char *s , t_mini *mini)
{
	int		i;
	int		len;
	char	symbol;

	i = 0;
	symbol = 0;
	while (s[i])
	{
		if (s[i] == '<' || s[i] == '>')
		{
			symbol = s[i];
			len = 0;
			while ((s[i] && s[i] == symbol))
			{
				i++;
				len++;
			}
			if (len > 2)
			{
				mini->check.symbols = (i < 3) ? s[i] : symbol;
				return (len);
			}
			while (s[i] == ' ')
				i++;
			if ((ft_isalpha(s[i]) || ft_isdigit(s[i])) && i < 3 && i >= 0)
			{
				symbol = 0;
				i++;
			}
			else if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]))
			{
				if ('>' == symbol && s[i] == '<')
					symbol = '<';
				mini->check.symbols = (i < 3) ? s[i] : symbol;
				printf("%c\n",mini->check.symbols);
				return (len);
			}
		}
		i++;
	}
	// mini->check.symbols = s[i];
	return (0);
}

void	check_symbols(t_mini *mini)
{
	int		res;

	res = if_error_symbols(mini->input, mini);
	if (res < 3 && res != 0)
		error_newline(mini);
	else if (res < 4 && mini->check.symbols == '<')
		error_newline(mini);
	else if (res > 2)
		error_symbols_left(mini, res);
}