/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:46:50 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/08 14:41:03 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int		get_value(t_mini *mini, int i)//get value exmpl (echo "test;;;")
{
	int pos;

	pos = i + 1;
	// printf("{%s}{%d}\n",mini->input + i,i);
	while (mini->input[pos] != '"' && mini->input[pos])
		pos++;
	if (mini->input[pos] == '"')
		mini->check.value = ft_substr(mini->input, i + 1, pos - i - 1);
	return (pos + 1);
}


void ft_error_end(char *s, char c) // error return
{
	c = 0;
	// printf("\n||%c||", c);
	printf("miniupdate: syntax error near unexpected token `%s'\n",s);
	exit(1) ;
}
void	end_cmd_check(t_mini *mini, int  i) // check if ';;' double in the same line
{

	while (mini->input[i])
	{
		// printf("{%s}{%d}\n",mini->input + i,i);
		// printf("{%d}{%zu}\n",i,ft_strlen(mini->input));
		while (mini->input[i] == ' ')
			i++;
		if (mini->input[i] == ';')
		{
			//(mini->input[i + 1] == ';') ? ft_error_end(";;", '\0') : (mini->check.end = 1);
			(mini->input[i + 1] != ';' && mini->input[i + 1] && mini->input[i + 1] != ' ') ? (mini->check.end = 0) : (void)0;
			i++;
		}
		while (mini->input[i] == ' ')
			i++;
		(mini->input[i] == ';' && mini->check.end == 1) ? ft_error_end(";", mini->input[i]) : (mini->check.end = 0);
		if (mini->input[i] == '"') // 
			i = get_value(mini,i);
		else
			i++;
	}
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
	end_cmd_check(mini, i);
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
	// if (mini->check.value)
	// 	printf("%s\n",mini->check.value);
	// mini->path_value = ft_lstsearch(mini->myenv, "PATH");
	// mini->paths = ft_split(mini->path_value, ':');
}