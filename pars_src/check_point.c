/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:46:50 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/08 11:38:38 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_error_end(char *s, char c)
{
	c = 0;
	// printf("\n||%c||", c);
	printf("miniupdate: syntax error near unexpected token `%s'\n",s);
	exit(1) ;
}

void	ft_check_err(t_mini	*mini)
{
	int		i;

	i = 0;
	while (mini->input[i])
	{
		while (mini->input[i] == ' ')
			i++;
		if (mini->input[i] == ';')
		{
			if (mini->input[i + 1] == ';')
				ft_error_end(";;", '\0');
			ft_error_end(";", '\0');
		}
		break ;
	}
	while (mini->input[i])
	{
		while (mini->input[i] == ' ')
			i++;
		if (mini->input[i] == ';')
		{
			(mini->input[i + 1] == ';') ? ft_error_end(";;", '\0') : (mini->check.end = 1);
			(mini->input[i + 1] != ';' && mini->input[i + 1] && mini->input[i + 1] != ' ') ? (mini->check.end = 0) : (void)0;
			i++;
		}
		while (mini->input[i] == ' ')
			i++;
		(mini->input[i] == ';' && mini->check.end == 1) ? ft_error_end(";", mini->input[i]) : (mini->check.end = 0);
		i++;
	}
	return ;
}



void	ft_check_point(t_mini *mini)
{
	int i;
	// char **splt;

	i = 0;
	ft_check_err(mini);
	// splt = ft_split(mini->input, ';');
	// while (splt[i])
	// {
	//		TO DO
	// 		i++;
	// }
}

void	parse(t_mini *mini)
{
	ft_check_point(mini);
	// mini->path_value = ft_lstsearch(mini->myenv, "PATH");
	// mini->paths = ft_split(mini->path_value, ':');
}