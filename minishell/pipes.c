/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:58:25 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 09:01:42 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipes_2(t_minishell *ms, int count, int *fd, int *fd_2)
{
	if (count + 1 == ms->pipe_count && count % 2 == 0)
	{
		if (ms->commands_current->fd_out != 1)
			dup2(ms->commands_current->fd_out, 1);
		close(fd[1]);
		dup2(fd[0], 0);
		return (1);
	}
	if (count == 0 && ms->pipe_count > 1)
	{
		if (ms->commands_current->fd_out != 0)
			dup2(ms->commands_current->fd_in, 0);
		close(fd_2[0]);
		dup2(fd_2[1], 1);
		return (1);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd_2[0]);
		dup2(fd_2[1], 1);
		return (1);
	}
	return (1);
}

int	pipes(t_minishell *ms, int count, int *fd, int *fd_2)
{
	if (ms->commands_current->fd_in < 0 || ms->commands_current->fd_out < 0)
	{
		printf("minishell: wrong file: %s\n", ms->cmd);
		return (0);
	}
	if (count == 0 && ms->pipe_count == 1)
	{
		if (ms->commands_current->fd_out != 0)
			dup2(ms->commands_current->fd_in, 0);
		if (ms->commands_current->fd_out != 1)
			dup2(ms->commands_current->fd_out, 1);
		return (1);
	}
	if (count + 1 == ms->pipe_count && count % 2 != 0)
	{
		if (ms->commands_current->fd_out != 1)
			dup2(ms->commands_current->fd_out, 1);
		close(fd[1]);
		dup2(fd[0], 0);
		return (1);
	}
	return (pipes_2(ms, count, fd, fd_2));
}
