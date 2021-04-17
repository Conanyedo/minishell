/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:58:40 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/17 14:17:47 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_mini *mini, int ac, char **av)
{
	(void)ac;
	(void)av;
	(*mini).myenv = (t_env *){0};
	(*mini).check = (t_checkers){0};
	(*mini).cmd = (t_cmd *){0};
	(*mini) = (t_mini){0};
}

void	execution(t_mini *mini)
{
	t_cmd	*cmd;
	t_pipe	*pip;

	ft_dup(mini);
	cmd = mini->cmd;
	while (cmd)
	{
		prepare_pipes(mini, cmd->pipes);
		pip = cmd->pipe;
		while (pip)
		{
			expansions(mini, pip, 0, 0);
			redir(mini, &pip, 0);
			mini->tabu = ft_strsplit(pip->content, " ", 1);
			tilde(mini);
			mini->tabu = remove_dust(&mini->tabu);
			commands(mini, cmd, pip);
			free_pipe(mini, &pip);
		}
		close_pipes(mini, cmd->pipes);
		free_cmd(&cmd);
	}
	close(mini->oldinput);
	close(mini->oldoutput);
}

int	main(int ac, char **av, char **env)
{
	t_mini			mini;
	struct termios	term;

	init(&mini, ac, av);
	g_mini = &mini;
	init_env(env, &mini.myenv);
	fill_hist(&mini.hist);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (1)
	{
		prompt(&mini);
		mini.input = readline(&mini, &mini.hist, &term);
		parse(&mini);
		tcgetattr(0, &term);
		if (!mini.status)
			execution(&mini);
		tcsetattr(0, TCSANOW, &term);
		free(mini.input);
		mini.input = NULL;
	}
}
