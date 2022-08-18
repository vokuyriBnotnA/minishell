/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:19:18 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 10:15:18 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	history_add(int fd_history)
{
	char	*str;

	while (1)
	{
		str = get_next_line(fd_history);
		if (str == NULL)
			break ;
		str[ft_strlen(str) - 1] = 0;
		add_history(str);
		free(str);
	}
	return (1);
}

int	history_init(t_minishell *ms)
{
	int		fd_history;
	char	*filename;

	filename = ft_strjoin(ms->path, "/.history");
	fd_history = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd_history < 0)
	{
		printf("minishell: History file error\n");
		return (0);
	}
	history_add(fd_history);
	free(filename);
	close(fd_history);
	return (1);
}

int	ms_history_add(t_minishell *ms)
{
	int		fd;
	char	*filename;

	filename = ft_strjoin(ms->path, "/.history");
	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("minishell: History file error\n");
		return (0);
	}
	write(fd, ms->cmd, strlen(ms->cmd));
	add_history(ms->cmd);
	write(fd, "\n", 1);
	close (fd);
	free(filename);
	return (1);
}

int	ms_history_print(t_minishell *ms)
{
	int		i;
	int		fd;
	char	*str;
	char	*filename;

	filename = ft_strjoin(ms->path, "/.history");
	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		printf("minishell: History file error\n");
		return (0);
	}
	i = 1;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		printf("   %d  %s", i, str);
		free (str);
	}
	close (fd);
	free(filename);
	return (1);
}
