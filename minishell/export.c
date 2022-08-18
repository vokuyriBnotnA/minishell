/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 04:10:25 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 10:18:41 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_export(t_minishell *ms)
{
	char	**cmd;
	int		fd;
	char	*filename;
	pid_t	pid;

	filename = ft_strjoin(ms->path, "/.export");
	cmd = malloc(sizeof(char *) * 3);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	cmd[0] = "sort";
	cmd[1] = NULL;
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, 0);
		if (execve("/usr/bin/sort", cmd, ms->envp) == -1)
			exit (1);
		exit (0);
	}
	waitpid(pid, NULL, 0);
	free(filename);
	return (1);
}

int	export_ms(t_minishell *ms)
{
	int		fd;
	char	*filename;

	filename = ft_strjoin(ms->path, "/.export");
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	ms->var_current = ms->var->next;
	while (ms->var_current != NULL)
	{
		write(fd, "declare -x ", 12);
		write(fd, ms->var_current->name, ft_strlen(ms->var_current->name));
		write(fd, "=", 1);
		write(fd, ms->var_current->name, ft_strlen(ms->var_current->name));
		write(fd, "\n", 1);
		ms->var_current = ms->var_current->next;
	}
	close(fd);
	free(filename);
	print_export(ms);
	return (1);
}
