/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 04:48:46 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 10:36:32 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(t_minishell *ms)
{
	int		fd;
	char	*filename;
	char	*str;

	filename = ft_strjoin(ms->path, "/.here_doc");
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	while (1)
	{
		write(0, "> ", 2);
		str = get_next_line(0);
		if (compare_str(str, ms->commands_current->here_doc_flag, \
		ft_strlen(str) - 1))
			break ;
		write(fd, str, ft_strlen(str));
		free(str);
	}
	close (fd);
	free(ms->commands_current->here_doc_flag);
	ms->commands_current->here_doc_flag = NULL;
	ms->commands_current->fd_in = open(filename, O_RDONLY);
	free(filename);
	return (1);
}
