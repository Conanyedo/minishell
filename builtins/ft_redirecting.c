/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirecting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:11:31 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/14 19:05:41 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		count_redirec(char		*input)
{
	int		i;
	char	dp;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			dp = input[i++];
			while (input[i] != dp)
				i++;
		}
		if (input[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

void    check_redirec(t_mini	*mini)
{
	int     i;
	int		res;
	char	**splt;

	mini->fd = 0;
	i = 1;
	res = count_redirec(mini->tab[0]);
	if (res)
	{
		splt = ft_strsplit(mini->tab[0], ">", 0);
		mini->fd = open(splt[1], O_CREAT | O_WRONLY, 0666);
		if (mini->fd < 0)
		{
			error_file(splt[1], mini);
			return ;
		}
		ft_strlcpy(mini->tab[0], splt[0], ft_strlen(splt[0]) + 1);
	}
	while (mini->tab[i])
	{
		res = count_redirec(mini->tab[i]);
		if (res)
		{
			mini->fd = open(mini->tab[i + 1], O_CREAT | O_WRONLY, 0666);
			if (mini->fd < 0)
			{
				error_file(mini->tab[i + 1], mini);
				return ;
			}
			free(mini->tab[i]);
			mini->tab[i] = NULL;
		}
		i++;
	}
	dup2(mini->fd, 1);
}