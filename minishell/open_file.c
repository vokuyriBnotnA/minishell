/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:04:59 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 10:36:54 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(t_minishell *ms, char *filename, char type)
{
	if (type == '<' && ms->commands_current->here_doc_flag != NULL)
	{
		ms->commands_current->here_doc_flag = filename;
		here_doc(ms);
		return (2);
	}
	if (type == '<' && ms->commands_current->here_doc_flag == 0)
		ms->commands_current->fd_in = open(filename, O_RDONLY);
	if (type == '>' && ms->commands_current->redir_output_append == 1)
		ms->commands_current->fd_out = open(filename, \
		O_CREAT | O_RDWR | O_APPEND, 0644);
	if (type == '>' && ms->commands_current->redir_output_append == 0)
		ms->commands_current->fd_out = open(filename, \
		O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (1);
}
