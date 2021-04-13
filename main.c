/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:58:40 by ybouddou          #+#    #+#             */
/*   Updated: 2021/04/12 15:37:41 by cabouelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd	**cmd)
{
	t_cmd	*prev;

	prev = (*cmd);
	(*cmd) = (*cmd)->next;
	if (prev->content)
		free(prev->content);
	free(prev);
}

void	free_pipe(t_pipe **pip)
{
	t_pipe	*prev;

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

	mini->ret = 0;
	ft_dup(mini);
	cmd = mini->cmd;
	while (cmd)
	{
		pip = cmd->pipe;
		while (pip)
		{
			expansions(mini, pip, 0, 0);
			redir(mini, &pip, 0);
			mini->tabu = ft_strsplit(pip->content, " ", 1);
			tilde(mini);
			mini->tabu = remove_dust(&mini->tabu);
			commands(mini, pip);
			ft_free(&mini->tabu);
			mini->tabu = NULL;
			free_pipe(&pip);
		}
		free_cmd(&cmd);
	}
	close(mini->oldinput);
	close(mini->oldoutput);
}

int	main(int ac, char **av, char **env)
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
		if (!mini.status)
			execution(&mini);
		free(mini.input);
		mini.input = NULL;
	}
}
