/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 15:58:40 by ybouddou          #+#    #+#             */
/*   Updated: 2021/03/22 18:01:14 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ifexist(t_mini *mini)
{
	int		i;
	int		fd;
	char	*slashcmd;

	i = 0;
	mini->path_value = ft_lstsearch(mini->myenv, "PATH");
	mini->paths = (mini->path_value) ? ft_split(mini->path_value, ':') : NULL;
	slashcmd = ft_strjoin("/", mini->tab[0]);
	while (mini->paths[i])
	{
		mini->cmd_exist = ft_strjoin(mini->paths[i], slashcmd);
		if ((fd = open(mini->cmd_exist, O_RDONLY)) > 0)
		{
			free(mini->tab[0]);
			mini->tab[0] = ft_strdup(mini->cmd_exist);
			close(fd);
			free(slashcmd);
			ft_free(mini->paths);
			free(mini->cmd_exist);
			return (1);
		}
		free(mini->cmd_exist);
		i++;
	}
	free(slashcmd);
	ft_free(mini->paths);
	return (0);
}

void	commands(t_mini *mini)
{
	if (is_builtins(mini))
		do_builtins(mini);
	else
		exec_cmd(mini);
	if (mini->fd[0] > 1)
		close(mini->fd[0]);
}

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
			redir(mini, 0);
			mini->tab = ft_strsplit(pipe->content, " ", 1);
			tilde(mini);
			mini->tab = remove_dust(mini->tab);
			commands(mini);
			ft_free(mini->tab);
			mini->tab = NULL;
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
	if (g_mini->pid)
		ft_putstr_fd("Quit: 3\n", 1);
	else
		ft_putstr_fd("\033[2D\033[K", 1);
}

void	handle_ctrl_d(t_mini *mini)
{
	while (!mini->r && *mini->input)
	{
		ft_putstr_fd("\033[K", 1);
		free(mini->input);
		mini->r = get_next_line(0, &mini->input);
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
	init_env(env, &mini.myenv);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (1)
	{
		g_mini = &mini;
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
