/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:50:08 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/25 12:34:55 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tilde(t_mini *mini)
{
	int		i;

	i = 0;
	mini->tmp = NULL;
	while (mini->tab[i])
	{
		if (mini->tab[i][0] == '~' && (mini->tab[i][1] == '/'
			|| !mini->tab[i][1]))
		{
			mini->tmp = ft_strjoin(ft_lstsearch(mini->myenv, "HOME"),
				mini->tab[i] + 1);
			free(mini->tab[i]);
			mini->tab[i] = ft_strdup(mini->tmp);
			free(mini->tmp);
			mini->tmp = NULL;
		}
		i++;
	}
}

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

void	dollar(t_mini *mini, t_pipe *pipe, int i, char **tmp)
{
	char	*value;
	char	join[2];
	char	*temp;

	value = ft_substr(pipe->content, i,\
		checksymbol(pipe->content, i + 1) - i);
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
	join[0] = '"' * -1;
	join[1] = '\0';
	temp = ft_strjoin(join, *tmp);
	free(*tmp);
	*tmp = ft_strjoin(temp, join);
	free(temp);
}

void	expansions(t_mini *mini, t_pipe *pipe)
{
	int		i;
	char	s;
	char	*tmp;

	i = 0;
	s = 0;
	mini->tmp = pipe->content;
	mini->temp = ft_strdup("");
	while (mini->tmp[i])
	{
		if (s == mini->tmp[i] * -1)
			s = 0;
		else if (mini->tmp[i] < 0)
			s = mini->tmp[i] * -1;
		if (mini->tmp[i] == '$' && s != '\'' && mini->tmp[i - 1] != 1)
			dollar(mini, pipe, i, &tmp);
		else
			tmp = ft_substr(mini->tmp, i, checksymbol(mini->tmp, i + 1) - i);
		i = checksymbol(mini->tmp, i + 1);
		mini->temp = ft_strjoin(mini->temp, tmp);
		free(tmp);
	}
	free(pipe->content);
	pipe->content = ft_strdup(mini->temp);
	free(mini->temp);
}
