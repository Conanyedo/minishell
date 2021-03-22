/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:50:08 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/20 18:27:33 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		checksymbol(char *tab, int i)
{
	if (tab[i] == '?')
		return (++i);
	if (ft_isdigit(tab[i]) && tab[i - 1] == '$')
		return (++i);
	while (tab[i] && (ft_isalnum(tab[i]) || tab[i] == '_'))
		i++;
	return (i);
}

void	dollar(t_mini *mini, int i, char **tmp)
{
	char	*value;

	value = ft_substr(mini->cmd->pipe->content, i,\
		checksymbol(mini->cmd->pipe->content, i + 1) - i);
	if (!ft_strncmp(value, "$", ft_strlen(value)))
	{
		*tmp = ft_strdup("$");
		return ;
	}
	value = ft_strchr(value, '$') + 1;
	if (!ft_strncmp(value, "?", ft_strlen(value)))
		*tmp = ft_strdup(ft_itoa(mini->cmd_status));
	else if (ft_lstsearch(mini->myenv, value))
		*tmp = ft_strdup(ft_lstsearch(mini->myenv, value));
	else
		*tmp = ft_strdup("");
}

void	expansions(t_mini *mini)
{
	int		i;
	char	s;
	char	*tmp;

	i = 0;
	s = 0;
	mini->tmp = mini->cmd->pipe->content;
	mini->temp = ft_strdup("");
	while (mini->tmp[i])
	{
		if (s == mini->tmp[i] * -1)
			s = 0;
		else if (mini->tmp[i] < 0)
			s = mini->tmp[i] * -1;
		if (mini->tmp[i] == '$' && mini->tmp[i + 1] && s != '\'' && mini->tmp[i - 1] != 1)
			dollar(mini, i, &tmp);
		else
			tmp = ft_substr(mini->tmp, i, checksymbol(mini->tmp, i + 1) - i);
		i = checksymbol(mini->tmp, i + 1);
		mini->temp = ft_strjoin(mini->temp, tmp);
		free(tmp);
	}
	free(mini->cmd->pipe->content);
	mini->cmd->pipe->content = ft_strdup(mini->temp);
	free(mini->temp);
}