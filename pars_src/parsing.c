/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:55:23 by cabouelw          #+#    #+#             */
/*   Updated: 2021/04/16 14:05:18 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_pipe(t_mini *mini, t_cmd **cmd, int i)
{
	t_pipe	*pipe;
	int		j;

	pipe = NULL;
	(*cmd)->content = ft_strtrim(mini->cmds[i], " \t");
	mini->tabu = ft_strsplit((*cmd)->content, "|", 1);
	(*cmd)->pipe = NULL;
	(*cmd)->pipe = (t_pipe *)malloc(sizeof(t_pipe));
	(*cmd)->pipe->next = NULL;
	(*cmd)->pipe->content = NULL;
	pipe = (*cmd)->pipe;
	j = -1;
	while (mini->tabu[++j])
	{
		(*cmd)->pipes = 1;
		pipe->content = ft_strtrim(mini->tabu[j], " \t");
		if (!mini->tabu[j + 1])
			break ;
		pipe->next = (t_pipe *)malloc(sizeof(t_pipe));
		pipe = pipe->next;
	}
	pipe->next = NULL;
	(*cmd)->pipes = j;
	ft_free(&mini->tabu);
	mini->tabu = NULL;
}

void	splitting(t_mini *mini)
{
	int		i;
	t_cmd	*cmd;

	i = -1;
	mini->tabu = NULL;
	cmd = NULL;
	mini->cmd = NULL;
	mini->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	mini->cmd->next = NULL;
	mini->cmd->content = NULL;
	mini->cmd->pipe = NULL;
	mini->cmd->pipes = 0;
	cmd = mini->cmd;
	while (mini->cmds[++i])
	{
		split_pipe(mini, &cmd, i);
		if (!mini->cmds[i + 1])
			break ;
		cmd->next = (t_cmd *)malloc(sizeof(t_cmd));
		cmd = cmd->next;
		cmd->content = NULL;
	}
	cmd->next = NULL;
	ft_free(&mini->cmds);
	mini->cmds = NULL;
}

int	loop_check(t_mini *mini, int i)
{
	if (mini->input[i] == '\\' && mini->check.quota == 0)
	{
		mini->check.symbols = 0;
		mini->check.left = 0;
		mini->check.right = 0;
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
	return (i);
}

void	checker(t_mini *mini, int i)
{
	mini->check = (t_checkers){0};
	while (mini->input[i] && !mini->status)
	{
		if (!ft_isalnum(mini->input[i]))
			i = loop_check(mini, i);
		else
			check_all(mini, 0, i);
		if (!ft_isexist("; |", mini->input[i]) && mini->input[i])
		{
			mini->check.point = 0;
			mini->check.pipe = 0;
		}
		if (!ft_isexist("|><; ", mini->input[i]) && mini->input[i])
		{
			mini->check.symbols = 0;
			mini->check.left = 0;
			mini->check.right = 0;
		}
		i++;
	}
	if (mini->status == 0)
		check_all(mini, 1, i);
}

void	parse(t_mini *mini)
{
	int		i;
	char	*tmp;

	i = 0;
	while (mini->input[i] == ' ')
		i++;
	if (ft_isexist(";|", mini->input[i]))
		error_symbols(mini, i);
	checker(mini, 0);
	if (mini->status)
		return ;
	tmp = mini->input;
	mini->input = ft_strtrim(mini->input, " \t");
	free(tmp);
	mini->cmds = ft_strsplit(mini->input, ";", 1);
	splitting(mini);
}
