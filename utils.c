/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 14:39:04 by cabouelw          #+#    #+#             */
/*   Updated: 2021/04/17 14:09:37 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char ***arr)
{
	int		i;

	i = 0;
	while ((*arr) && (*arr)[i])
	{
		if ((*arr)[i])
			free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	if ((*arr))
		free((*arr));
	(*arr) = NULL;
}

void	close_fd(t_mini *mini)
{
	if (mini->fd[1])
	{
		close(mini->fd[1]);
		mini->fd[1] = 0;
	}
	if (mini->fd[0])
	{
		close(mini->fd[0]);
		mini->fd[0] = 0;
	}
}

int	isredirect_loop(t_mini *mini, char *s, int i)
{
	int		point;

	while (s[i] == '/' || s[i] == '.')
	{
		point = 0;
		while (s[i] == '.')
		{
			if (point > 1)
			{
				error_file(mini, s, "");
				return (-1);
			}
			point++;
			i++;
		}
		i++;
	}
	return (i);
}

void	ft_dup(t_mini *mini)
{
	mini->oldinput = dup(0);
	mini->oldoutput = dup(1);
}

void	if_isdirect(t_mini *mini, char *s)
{
	int		i;

	i = 0;
	if (stat(s, &mini->stt) && s[0] == '/')
		return (error_file(mini, s, ""));
	if (mini->stt.st_mode & S_IFMT & S_IFDIR && s[0] == '/')
		return (is_directory(mini, mini->tabu[0]));
	while (s[i] == '.')
		i++;
	if (i == 1 && !s[i])
		return (error_arg(mini));
	if (i && (!s[i] || s[i] != '/'))
		return (cmd_not_found(mini));
	i = isredirect_loop(mini, s, i);
	if (i == -1)
		return ;
	if (!s[i] && i)
		return (is_directory(mini, mini->tabu[0]));
	mini->check.point = 0;
}
