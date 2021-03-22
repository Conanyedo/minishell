/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:55:23 by cabouelw          #+#    #+#             */
/*   Updated: 2021/03/22 10:29:38 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_pipe(t_mini *mini, t_cmd **cmd, int i)
{
	t_pipe	*pipe;
	int		j;

	pipe = NULL;
	(*cmd)->content = ft_strtrim(mini->cmds[i], " \t");
	mini->tab = ft_strsplit((*cmd)->content, "|", 1);
	(*cmd)->pipe = NULL;
	(*cmd)->pipe = (t_pipe*)malloc(sizeof(t_pipe));
	(*cmd)->pipe->next = NULL;
	pipe = (*cmd)->pipe;
	j = -1;
	while (mini->tab[++j])
	{
		pipe->content = ft_strtrim(mini->tab[j], " \t");
		if (!mini->tab[j + 1])
			break ;
		pipe->next = (t_pipe*)malloc(sizeof(t_pipe));
		pipe = pipe->next;
	}
	pipe->next = NULL;
	ft_free(mini->tab);
	mini->tab = NULL;
}

void	splitting(t_mini *mini)
{
	int		i;
	t_cmd	*cmd;

	i = -1;
	mini->tab = NULL;
	cmd = NULL;
	mini->cmd = NULL;
	mini->cmd = (t_cmd*)malloc(sizeof(t_cmd));
	mini->cmd->next = NULL;
	mini->cmd->pipe = NULL;
	cmd = mini->cmd;
	while (mini->cmds[++i])
	{
		split_pipe(mini, &cmd, i);
		if (!mini->cmds[i + 1])
			break ;
		cmd->next = (t_cmd*)malloc(sizeof(t_cmd));
		cmd = cmd->next;
	}
	cmd->next = NULL;
	ft_free(mini->cmds);
	mini->cmds = NULL;
}

char	**remove_dust(char **str)
{
	int		i;
	int		j;
	int		t;
	char	**cpy;

	t = 0;
	while (str[t])
		t++;
	cpy = (char**)malloc(sizeof(char*) * t + 1);
	t = -1;
	while (str[++t])
	{
		cpy[t] = (char*)malloc(sizeof(char) * ft_strlen(str[t]) + 1);
		i = -1;
		j = 0;
		while (str[t][++i] != '\0')
			if (str[t][i] > 0)
				cpy[t][j++] = str[t][i];
		cpy[t][j] = '\0';
	}
	cpy[t] = NULL;
	return (cpy);
}

void	check_all(t_mini *mini, int i, int idx)
{
	if (i == 1)
	{
		if (mini->check.dbl_quota)
			ft_error_end("\"", mini);
		else if (mini->check.quota)
			ft_error_end("'", mini);
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
		return ('\\' * -1);
	else if (mini->input[i + 1] && mini->input[i + 1] == '$')
		return (1);
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
			break ;
		if (mini->input[i] == '\\' && mini->check.quota == 0)
		{
			mini->input[i] = check_slash(mini, i);
			i++;
		}
		else if (mini->input[i] == ';')
			check_point(mini, i);
		else if (mini->input[i] == '|')
			check_pipes(mini, i);
		else if (mini->input[i] == '"')
			check_bdl_quot(mini, i);
		else if (mini->input[i] == '\'')
			check_one_quot(mini, i);
		else if (mini->input[i] == '<' || mini->input[i] == '>')
			check_symbols(mini, i);
		else if (ft_isalnum(mini->input[i]) && mini->input[i] != ';'
			&& mini->input[i] != ' ')
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
	mini->input = ft_strtrim(mini->input, " \t");
	checker(mini);
	if (mini->status)
		return ;
	mini->cmds = ft_strsplit(mini->input, ";", 1);
	splitting(mini);
}
