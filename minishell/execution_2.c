/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 08:40:46 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 10:20:40 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution_1(t_minishell *ms)
{
	ms->commands_current = ms->commands;
	while (ms->commands_current->next != NULL)
	{
		ms->commands_current->cmd_execve = ft_split(ms->commands_current->cmd, \
			' ');
		if (is_my_func(ms->commands_current->cmd_execve[0])
			|| is_my_func_child(ms->commands_current->cmd_execve[0]))
			ms->commands_current->my_func = 1;
		if (access(ms->commands_current->cmd_execve[0], F_OK) == 0)
		{
			ms->commands_current->path = \
			dup_str(ms->commands_current->cmd_execve[0]);
			break ;
		}
		ms->commands_current->path = \
		path_func(ms->commands_current->cmd_execve[0], ms->envp);
		ms->commands_current = ms->commands_current->next;
	}
	return (1);
}

int	execution_2(t_minishell *ms, pid_t **pid)
{
	pid[0] = malloc(sizeof(pid_t) * (ms->pipe_count + 1));
	if (!pid[0])
	{
		printf("minishell: pid error\n");
		return (0);
	}
	return (1);
}

int	execution_3(t_minishell *ms)
{
	int	i;

	i = 0;
	ms->commands_current = ms->commands;
	while (ms->commands_current->next != NULL)
	{
		if ((!ms->commands_current->path
				|| !*ms->commands_current->path)
			&& ms->commands_current->my_func == 0)
		{
			printf("%s : command not found\n", ms->cmd);
			return (0);
		}
		ms->commands_current = ms->commands_current->next;
	}
	return (1);
}

int	execution_pipe(t_minishell *ms, int *fd, int *fd_2, int i)
{
	if (i % 2 == 0 && i + 1 != ms->pipe_count)
		pipe(fd);
	else if (i % 2 != 0 && i + 1 != ms->pipe_count)
		pipe(fd_2);
	return (1);
}

int	execution_work(t_minishell *ms, int *fd, int *fd_2, pid_t *pid)
{
	pid[ms->i] = fork();
	if (pid[ms->i] == 0)
	{
		if (ms->i % 2 == 0)
		{
			if (!pipes(ms, ms->i, fd_2, fd))
				return (0);
		}
		else if (ms->i % 2 != 0)
			if (!pipes(ms, ms->i, fd, fd_2))
				return (0);
		if (ms->commands_current->my_func == 1 \
		&& is_my_func_child(ms->commands_current->cmd_execve[0]))
		{
			if (!my_func_child(ms->commands_current->cmd_execve[0], \
			ms->commands_current->cmd_execve, ms))
				printf("minishell: Worng command: %s\n", \
				ms->commands_current->cmd);
		}
		else if (execve(ms->commands_current->path, \
		ms->commands_current->cmd_execve, ms->envp) == -1)
			exit (1);
		exit(0);
	}
	return (1);
}
