/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 09:36:40 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/09 11:02:29 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtins(t_mini *mini)
{
	if (!(ft_strncmp(mini->input, "env", ft_strlen(mini->input))))
		return (1);
	else if (!(ft_strncmp(mini->input, "echo", ft_strlen(mini->input))))
		return (1);
	else if (!(ft_strncmp(mini->input, "pwd", ft_strlen(mini->input))))
		return (1);
	else if (!(ft_strncmp(mini->input, "cd", ft_strlen(mini->input))))
		return (1);
	else if (!(ft_strncmp(mini->input, "exit", ft_strlen(mini->input))))
		return (1);
	else if (!(ft_strncmp(mini->input, "export", ft_strlen(mini->input))))
		return (1);
	else if (!(ft_strncmp(mini->input, "unset", ft_strlen(mini->input))))
		return (1);
	return (0);
}

void	do_builtins(t_mini *mini)
{
	if (!(ft_strncmp(mini->input, "env", ft_strlen(mini->input))))
		ft_env(mini->myenv);
	else if (!(ft_strncmp(mini->input, "echo", ft_strlen(mini->input))))
		ft_echo(&mini->input);
	else if (!(ft_strncmp(mini->input, "exit", ft_strlen(mini->input))))
		ft_exit(mini);
}