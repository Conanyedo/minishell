/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:03:14 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/11 11:48:34 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_env(char *tab)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * 3);
	while (tab[i] && tab[i] != '=')
		i++;
	if (!tab[i])
		ft_putstr_fd("declare -x ", 1);
	return (tmp);
}

void	print_export(t_mini *mini)
{
	t_env	*fresh;

	fresh = mini->myenv;
	while (fresh)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(fresh->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(fresh->value, 1);
		ft_putstr_fd("\n", 1);
		fresh = fresh->next;
	}
}

// void	add_env(t_mini *mini)
// {
	
// }

// void	edit_env(t_mini *mini)
// {
	
// }

void	ft_export(t_mini *mini)
{
	int		i;
	char	**splitted;

	i = 0;
	splitted = NULL;
	mini->tab++;
	if (!mini->tab[i])
	{
		print_export(mini);
		return ;
	}
	while (mini->tab[i])
	{
		splitted = split_env(mini->tab[i]);
		// if (ft_lstsearch(mini->myenv, mini->tab[i]))
		// 	edit_env(mini);
		// else
		i++;
	}
}