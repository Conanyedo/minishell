/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:58:40 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/10 18:50:59 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_mini *mini, char **env)
{
	// t_cmd	*list;
	// t_pipe	*pipelist;
	
	// list = NULL;
	// pipelist = NULL;
	// list = mini->cmd_list;
	while (!mini->status && mini->cmd_list)
	{
		mini->tab = ft_strsplit(mini->cmd_list->pipe->content, " ", 1);
		if (is_builtins(mini))
			do_builtins(mini);
		else
			exec_cmd(mini, env);
		mini->cmd_list = mini->cmd_list->next;
	}
}

int		main(int ac, char **av, char **env)
{
	t_mini	mini;
	
	(void)ac;
	(void)av;
	mini.myenv = (t_env *){0};
	mini.check = (t_checkers){0};
	mini.cmd_list = (t_cmd*){0};
	mini = (t_mini){0};
	init_env(env, &mini.myenv);
	while(1)
	{
		prompt(&mini);
		get_next_line(0, &mini.input);
		parse(&mini);
		execution(&mini, env);
		free(mini.input);
		mini.input = NULL;
	}
}