/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:20:27 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 11:35:54 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	g_exit_code = "1";
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signals(void)
{
	struct sigaction	sa;
	sigset_t			set;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	sa.sa_handler = ft_handler;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sa.sa_mask = set;
	sigaction(SIGINT, &sa, NULL);
}

void	free_ms_cmd(t_minishell *ms)
{
	t_commands	*prev;

	ms->commands_current = ms->commands;
	while (ms->commands_current != NULL)
	{
		prev = ms->commands_current;
		if (prev->cmd)
			free(prev->cmd);
		if (prev->cmd_execve)
			free_split(prev->cmd_execve);
		if (prev->here_doc_flag)
			free(prev->here_doc_flag);
		if (prev->path)
			free(prev->path);
		prev->here_doc_flag = NULL;
		prev->cmd = NULL;
		prev->cmd_execve = NULL;
		prev->path = NULL;
		prev->next = NULL;
		free(prev);
		prev = NULL;
		ms->commands_current = ms->commands_current->next;
	}
}

int	init_commands_from_read(t_minishell *ms)
{
	ms->commands = init_commands();
	if (!ms->commands)
	{
		printf("minishell: Init error\n");
		return (0);
	}
	ms->pipe_count = 0;
	return (1);
}

int	read_cmd(t_minishell *ms)
{
	while (1)
	{
		if (!init_commands_from_read(ms))
			return (0);
		ft_signals();
		ms->cmd = readline("ms-0.1$ ");
		if (!ms->cmd)
			break ;
		if (*ms->cmd)
		{
			ms_history_add(ms);
			if (!parsing(ms))
				printf("minishell: Parsing error\n");
			else
			{
				execution(ms);
				free_ms_cmd(ms);
			}
		}
		free (ms->cmd);
	}
	free_ms_cmd(ms);
	printf("exit\n");
	return (1);
}
