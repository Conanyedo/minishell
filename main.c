/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:58:40 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/08 10:03:17 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	t_mini	mini;
	
	(void)ac;
	(void)av;
	init_env(env, &mini.myenv);
	while(1)
	{
		prompt(mini.myenv, 1);
		get_next_line(0, &mini.input);
		parse(&mini);
		mini.pid = fork();
		if (mini.pid > 0)
			wait(NULL);
		else
		{
			if (builtins(&mini) == 1)
				do_builtins(&mini);
			else
			{
				*mini.argv = mini.input;
				mini.argv[1] = NULL;
				execve(mini.input, mini.argv, env);
			}
		}
		free(mini.input);
	}
}