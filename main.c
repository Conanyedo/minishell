/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:58:40 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/30 19:05:20 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_mini *mini)
{
	t_cmd	*cmd;
	t_pipe	*pip;

	cmd = NULL;
	pip = NULL;
	mini->p = 0;
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
			mini->tab = ft_strsplit(pip->content, " ", 1);
			tilde(mini);
			mini->tab = remove_dust(mini->tab);
			commands(mini, pip);
			ft_free(mini->tab);
			mini->tab = NULL;
			pip = pip->next;
		}
		cmd = cmd->next;
	}
	close(mini->oldinput);
	close(mini->oldoutput);
}

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\033[2D\033[K\n", 1);
	g_mini->cmd_status = 1;
	prompt(g_mini);
}

void	handle_sigquit(int sig)
{
	(void)sig;
	g_mini->tmp = NULL;
	g_mini->temp = ft_strdup("");
	if (g_mini->pid)
		return (ft_putstr_fd("Quit: 3\n", 1));
	if (!g_mini->r && !g_mini->input)
	{
		ft_putstr_fd("\033[2D\033[K", 1);
		return ;
	}
	while (!g_mini->r && g_mini->input)
	{
		ft_putstr_fd("\033[2D\033[K", 1);
		g_mini->temp = ft_strdup(g_mini->input);
		free(g_mini->input);
		g_mini->r = get_next_line(0, &g_mini->input);
		g_mini->tmp = ft_strjoin(g_mini->temp, g_mini->input);
		free(g_mini->input);
		g_mini->input = ft_strdup(g_mini->tmp);
	}
}

void	handle_ctrl_d(t_mini *mini)
{
	mini->tmp = NULL;
	mini->temp = ft_strdup("");
	while (!mini->r && *mini->input)
	{
		ft_putstr_fd("\033[K", 1);
		mini->temp = ft_strdup(mini->input);
		free(mini->input);
		mini->r = get_next_line(0, &mini->input);
		mini->tmp = ft_strjoin(mini->temp, mini->input);
		free(mini->input);
		mini->input = ft_strdup(mini->tmp);
	}
	if (!mini->r && !*mini->input)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
}

int		main(int ac, char **av, char **env)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	mini.myenv = (t_env *){0};
	mini.check = (t_checkers){0};
	mini.cmd = (t_cmd*){0};
	mini = (t_mini){0};
	g_mini = &mini;
	init_env(env, &mini.myenv);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (1)
	{
		prompt(&mini);
		mini.r = get_next_line(0, &mini.input);
		handle_ctrl_d(&mini);
		parse(&mini);
		if (!mini.status)
			execution(&mini);
		free(mini.input);
		mini.input = NULL;
	}
}
