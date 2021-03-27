/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:58:40 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/27 10:58:21 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_mini *mini)
{
	t_cmd	*cmd;
	t_pipe	*pipe;

	cmd = NULL;
	pipe = NULL;
	cmd = mini->cmd;
	while (cmd)
	{
		pipe = cmd->pipe;
		while (pipe)
		{
			expansions(mini, pipe);
			redir(mini, &pipe, 0);
			mini->tab = ft_strsplit(pipe->content, " ", 1);
			tilde(mini);
			mini->tab = remove_dust(mini->tab);
			commands(mini);
			ft_free(mini->tab);
			ft_free(mini->env_array);
			mini->tab = NULL;
			mini->env_array = NULL;
			pipe = pipe->next;
		}
		cmd = cmd->next;
	}
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
	if (!g_mini->r  && !g_mini->input)
	{
		ft_putstr_fd("\033[2D\033[K", 1);
		// printf("input : |%s|\n", g_mini->input);
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
		free(mini.cmd);
		mini.cmd = NULL;
		free(mini.input);
		mini.input = NULL;
	}
}
