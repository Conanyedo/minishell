/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:58:40 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/03 16:31:16 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	int		pid;
	char	*input;
	char	*argv[] = {NULL, NULL};
	t_env	*myenv;
	// int		i;
	
	(void)ac;
	(void)av;
	myenv = init_env(env);
	// while (myenv)
	// {
	// 	printf("%s=%s\n", myenv->key, myenv->value);
	// 	myenv = myenv->next;
	// }
	// i = 0;
	// while (env[i])
	// {
	// 	printf("%s\n", env[i]);
	// 	i++;
	// }
	while(1)
	{
		write(1, "\033[0;32m minishell~: \033[0m", 25);
		get_next_line(0, &input);
		*argv = input;
		pid = fork();
		if (pid > 0)
		{
			wait(NULL);
			printf("Parent's pid: %d\n", pid);
		}
		else
		{
			printf("Child's pid %d\n", pid);
			execve(input, argv, env);
		}
	}
	
}