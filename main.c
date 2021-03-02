/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:58:40 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/02 18:37:26 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	// int		pid;
	// char	*input;
	// char	*argv[] = {NULL, NULL};
	t_env	*myenv;
	int		i;
	
	(void)ac;
	(void)av;
	myenv = init_env(env);
	while (myenv)
	{
		printf("%s=%s\n", myenv->key, myenv->value);
		myenv = myenv->next;
	}
	i = 0;
	// while (env[i])
	// {
	// 	printf("%s\n", env[i]);
	// 	i++;
	// }
	// while(1)
	// {
	// 	write(1, "minishell~: ", 12);
	// 	get_next_line(0, &input);
	// 	*argv = input;
	// 	if ((pid = fork()) > 0)
	// 	{
	// 		printf("Parent pid: %d\n", pid);
	// 		wait(0);
	// 	}
	// 	else
	// 	{
	// 		printf("Child pid %d\n", pid);
	// 		execve(input, argv, env);
	// 	}
	// 	if (!ft_strncmp(input, "exit", ft_strlen(input)))
	// 		exit (1);
	// }
	
}