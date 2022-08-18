/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:55:21 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 08:41:26 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution_close(int *fd, int *fd_2, int i)
{
	if (i % 2 == 0 && i != 0)
	{
		close(fd_2[0]);
		close(fd_2[1]);
	}
	else if (i % 2 != 0)
	{
		close(fd[0]);
		close(fd[1]);
	}
	return (1);
}

int	execution_4(t_minishell *ms, pid_t *pid, int *fd, int *fd_2)
{
	int	i;

	ms->commands_current = ms->commands;
	i = 0;
	while (i < ms->pipe_count && ms->commands_current->next != NULL)
	{
		ms->i = i;
		execution_pipe(ms, fd, fd_2, i);
		if (ms->commands_current->my_func == 1
			&& is_my_func(ms->commands_current->cmd_execve[0]))
		{
			if (!my_func(ms->commands_current->cmd_execve[0], \
			ms->commands_current->cmd_execve, ms))
				printf("minishell: Worng command: %s\n", \
				ms->commands_current->cmd);
		}
		else
			execution_work(ms, fd, fd_2, pid);
		execution_close(fd, fd_2, i);
		ms->commands_current = ms->commands_current->next;
		i++;
	}
	return (1);
}

int	execution_end(t_minishell *ms, pid_t *pid, int *fd, int *fd_2)
{
	int	i;

	i = 0;
	while (i < ms->pipe_count)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	close(fd_2[0]);
	close(fd_2[1]);
	free(pid);
	return (1);
}

int	execution_main(t_minishell *ms, pid_t *pid, int *fd, int *fd_2)
{
	execution_1(ms);
	execution_2(ms, &pid);
	execution_3(ms);
	execution_4(ms, pid, fd, fd_2);
	execution_end(ms, pid, fd, fd_2);
	return (1);
}

int	execution(t_minishell *ms)
{
	pid_t	*pid;
	int		fd[2];
	int		fd_2[2];

	pid = NULL;
	execution_main(ms, pid, fd, fd_2);
	return (1);
}
