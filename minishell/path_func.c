/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 08:39:43 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 08:39:57 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_func(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**paths;
	char	*path_path;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path_path, cmd);
		free(path_path);
		if (access(path, F_OK) == 0)
		{
			free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(paths);
	return (NULL);
}
