/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:58:40 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/11 17:28:25 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd	**cmd)
{
	t_cmd *prev;
	
	prev = (*cmd);
	(*cmd) = (*cmd)->next;
	if (prev->content)
		free(prev->content);
	free(prev);
}

void	free_pipe(t_pipe **pip)
{
	t_pipe *prev;
	
	prev = (*pip);
	(*pip) = (*pip)->next;
	if (prev->content)
		free(prev->content);
	free(prev);
}

void	execution(t_mini *mini)
{
	t_cmd	*cmd;
	t_pipe	*pip;

	cmd = NULL;
	pip = NULL;
	mini->ret = 0;
	mini->oldinput = dup(0);
	mini->oldoutput = dup(1);
	cmd = mini->cmd;
	while (cmd)
	{
		pip = cmd->pipe;
		while (pip)
		{
			expansions(mini, pip);
			redir(mini, &pip, 0);
			mini->tabu = ft_strsplit(pip->content, " ", 1);
			tilde(mini);
			mini->tabu = remove_dust(&mini->tabu);
			commands(mini, pip);
			ft_free(&mini->tabu);
			mini->tabu = NULL;
			// pip = pip->next;
			free_pipe(&pip);
		}
		// cmd = cmd->next;
		free_cmd(&cmd);
	}
	close(mini->oldinput);
	close(mini->oldoutput);
}

int		main(int ac, char **av, char **env)
{
	t_mini			mini;
	struct termios	term;

	(void)ac;
	(void)av;
	(void)env;
	mini.myenv = (t_env *){0};
	mini.check = (t_checkers){0};
	mini.cmd = (t_cmd *){0};
	mini = (t_mini){0};
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
		// tcgetattr(0, &term);
		if (!mini.status)
			execution(&mini);
		// tcsetattr(0, TCSADRAIN, &term);
		free(mini.input);
		mini.input = NULL;
	}
}
