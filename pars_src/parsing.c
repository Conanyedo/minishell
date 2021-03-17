/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:55:23 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/16 18:19:48 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	splitting(t_mini *mini)
{
	int		i;
	int		j;
	char	**splitted;
	t_cmd	*list;
	t_pipe	*pipelist;

	i = 0;
	splitted = NULL;
	list = NULL;
	pipelist = NULL;
	mini->cmd_list = NULL;
	mini->cmd_list = (t_cmd*)malloc(sizeof(t_cmd));
	mini->cmd_list->next = NULL;
	mini->cmd_list->pipe = NULL;
	list = mini->cmd_list;
	while (mini->cmds[i])
	{
		list->content = ft_strtrim(mini->cmds[i], " \t");
		splitted = ft_strsplit(list->content, "|", 1);
		list->pipe = NULL;
		list->pipe = (t_pipe*)malloc(sizeof(t_pipe));
		list->pipe->next = NULL;
		pipelist = list->pipe;
		j = 0;
		while (splitted[j])
		{
			pipelist->content = ft_strtrim(splitted[j], " \t");
			if (!splitted[j + 1])
				break ;
			pipelist->next = (t_pipe*)malloc(sizeof(t_pipe));
			pipelist = pipelist->next;
			j++;
		}
		pipelist->next = NULL;
		ft_free(splitted);
		if (!mini->cmds[i + 1])
			break ;
		list->next = (t_cmd*)malloc(sizeof(t_cmd));
		list = list->next;
		i++;
	}
	list->next = NULL;
}

char	**remove_dust(char **str)
{
	int		i;
	int		j;
	int		t;
	char	**cpy;

	j = 0;
	t = 0;
	while (str[t])
		t++;
	cpy = (char**)malloc(sizeof(char*) * t + 1);
	t = 0;
	while (str[t])
	{
		cpy[t] = (char*)malloc(sizeof(char) * ft_strlen(str[t]) + 1);
		i = 0;
		j = 0;
		while (str[t][i] != '\0')
		{
			if (str[t][i] > 0)
				cpy[t][j++] = str[t][i];
			i++;
		}
		cpy[t][j] = '\0';
		t++;
	}
	cpy[t] = NULL;
	// ft_free(str);
	return(cpy);
}

void	check_all(t_mini *mini, int i, int idx)
{
	if (i == 1)
	{
		if (mini->check.dbl_quota)
			ft_error_end("\"",mini);
		else if (mini->check.quota)
			ft_error_end("'",mini);
		if (mini->check.right || mini->check.left)
			error_symbols(mini, idx);
	}
	else
	{
		if (mini->check.left > 3 || mini->check.left > 2)
			error_symbols(mini, idx);
	}
}

char	check_slash(t_mini *mini, int i)
{
	if (mini->input[i + 1] && mini->input[i + 1] == '\\')
		return('\\' * -1);
	else if (mini->check.dbl_quota)
	{
		if (mini->input[i + 1] == '"')
			return (mini->input[i] * -1);
		else if (mini->input[i + 1] == '\'')
			return (mini->input[i]);
	}
	else if (mini->check.quota)
	{
		if (mini->input[i + 1] == '"')
			return (mini->input[i]);
		else if (mini->input[i + 1] == '\'')
			return (mini->input[i] * -1);
	}
	return (mini->input[i] * -1);
}

void	checker(t_mini *mini)
{
	int		i;

	i = 0;
	mini->check = (t_checkers) {0};
	while (mini->input[i])
	{
		if (mini->status == 1)
			break;
		if (mini->input[i] == '\\' && mini->check.quota == 0)
		{
			mini->input[i] = check_slash(mini, i);
			i++;
		}
		else if (mini->input[i] == ';')
			check_point(mini, i);
		else if (mini->input[i] == '|')
			check_pipes(mini , i);
		else if (mini->input[i] == '"')
			check_bdl_quot(mini, i);
		else if (mini->input[i] == '\'')
			check_one_quot(mini, i);
		else if (mini->input[i] == '<' || mini->input[i] == '>')
			check_symbols(mini, i);
		else if (ft_isprint(mini->input[i]) && mini->input[i] != ';' && mini->input[i] != ' ')
		{
			mini->check.point = 0;
			mini->check.left = 0;
			mini->check.right = 0;
			mini->check.pipe = 0;
			mini->check.symbols = 0;
		}
		else
			check_all(mini, 0, i);
		i++;
	}
	if (mini->status == 0)
		check_all(mini, 1, i);
}

void	parse(t_mini *mini)
{
	// int i = 0;
	mini->input = ft_strtrim(mini->input, " \t");
	checker(mini);
	if (mini->status)
		return;
	mini->cmds = ft_strsplit(mini->input, ";", 1);
	splitting(mini);
	
	// t_cmd	*list;
	// t_pipe	*pipelist;
	// list = NULL;
	// pipelist = NULL;
	// list = mini->cmd_list;
	// while (list)
	// {
	// 	printf("|%s|\n", list->content);
	// 	pipelist = list->pipe;
	// 	while (pipelist)
	// 	{
	// 		printf("{%s}\n", pipelist->content);
	// 		pipelist = pipelist->next;
	// 	}
	// 	list = list->next;
	// }
	mini->path_value = ft_lstsearch(mini->myenv, "PATH");
	mini->paths = ft_split(mini->path_value, ':');
}