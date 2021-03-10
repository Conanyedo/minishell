/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:58:40 by ybouddou          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/03/10 10:54:30 by ybouddou         ###   ########.fr       */
=======
/*   Updated: 2021/03/09 15:01:51 by cabouelw         ###   ########.fr       */
>>>>>>> 54c10775de143488745de78850d1290c00d52aef
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	t_mini	mini;
	
	(void)ac;
	(void)av;
	mini.myenv = (t_env *){0};
	mini.check = (t_checkers){0};
	mini.cmd_list = (t_list**){0};
	mini = (t_mini){0};
	init_env(env, &mini.myenv);
	while(1)
	{
		prompt(&mini);
		get_next_line(0, &mini.input);
		parse(&mini);
		if (!mini.status)
		{
			if (is_builtins(&mini) == 1)
				do_builtins(&mini);
			else
				exec_cmd(&mini, env);
		}
		free(mini.input);
		mini.input = NULL;
	}
}