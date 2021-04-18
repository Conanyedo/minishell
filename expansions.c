/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:50:08 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/18 15:28:44 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tilde(t_mini *mini)
{
	int		i;

	i = 0;
	mini->tmp = NULL;
	while (mini->tabu[i])
	{
		if (mini->tabu[i][0] == '~' && (mini->tabu[i][1] == '/'
			|| !mini->tabu[i][1]))
		{
			mini->tmp = ft_strjoin(ft_lstsearch(mini->myenv, "HOME", \
				&mini->print), mini->tabu[i] + 1);
			free(mini->tabu[i]);
			mini->tabu[i] = ft_strdup(mini->tmp);
			free(mini->tmp);
			mini->tmp = NULL;
		}
		i++;
	}
}

int	checksymbol(char *tabu, int i)
{
	if (tabu[i] == '?' || tabu[i] < 0)
		return (++i);
	if ((ft_isdigit(tabu[i]) && tabu[i - 1] == '$'))
		return (++i);
	while (tabu[i] && (ft_isalnum(tabu[i]) || tabu[i] == '_'))
		i++;
	return (i);
}

void	dollar(t_mini *mini, char *tabu, int i, char **tmp)
{
	char	*value;
	char	*temp;

	value = ft_substr(tabu, i, checksymbol(tabu, i + 1) - i);
	if (!ft_strncmp(value, "$", ft_strlen(value)))
	{
		*tmp = ft_strdup("$");
		free(value);
		return ;
	}
	temp = value;
	value = ft_strchr(value, '$') + 1;
	free(temp);
	if (!ft_strncmp(value, "?", ft_strlen(value)))
		*tmp = ft_itoa(mini->cmd_status);
	else if (ft_lstsearch(mini->myenv, value, &mini->print) && mini->print != 1)
		*tmp = ft_strdup(ft_lstsearch(mini->myenv, value, &mini->print));
	else
	{
		*tmp = ft_strdup("");
		if (!mini->check.tmp)
			mini->check.tmp = ft_strjoin("$", value);
	}
}

void	expansions(t_mini *mini, t_pipe *pip, int i, int s)
{
	char	*temp;
	char	*tmp;

	mini->tmp = ft_strdup(pip->content);
	free(pip->content);
	mini->temp = ft_strdup("");
	while (mini->tmp[i])
	{
		if (s == mini->tmp[i] * -1)
			s = 0;
		else if (mini->tmp[i] < 0)
			s = mini->tmp[i] * -1;
		if (mini->tmp[i] == '$' && s != '\'' && mini->tmp[i - 1] != 1)
			dollar(mini, mini->tmp, i, &tmp);
		else
			tmp = ft_substr(mini->tmp, i, checksymbol(mini->tmp, i + 1) - i);
		i = checksymbol(mini->tmp, i + 1);
		temp = mini->temp;
		mini->temp = ft_strjoin(mini->temp, tmp);
		free(temp);
		free(tmp);
	}
	free(mini->tmp);
	pip->content = ft_strdup(mini->temp);
	free(mini->temp);
}
