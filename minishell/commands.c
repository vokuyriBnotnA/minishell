/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:01:38 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 05:08:15 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*init_commands(void)
{
	t_commands	*lst;

	lst = (t_commands *) malloc(sizeof(t_commands));
	if (!lst)
		return (NULL);
	lst->cmd = NULL;
	lst->cmd_execve = NULL;
	lst->path = NULL;
	lst->here_doc_flag = NULL;
	lst->redir_output_append = 0;
	lst->fd_in = 0;
	lst->fd_out = 1;
	lst->my_func = 0;
	lst->next = NULL;
	return (lst);
}

t_commands	*add_commands(t_commands *lst)
{
	t_commands	*temp;
	t_commands	*p;

	temp = (t_commands *) malloc(sizeof(t_commands));
	if (!temp)
		return (NULL);
	p = lst->next;
	lst->next = temp;
	temp->cmd = NULL;
	lst->cmd_execve = NULL;
	lst->path = NULL;
	temp->here_doc_flag = NULL;
	temp->fd_in = 0;
	temp->fd_in = 1;
	temp->interpret_flag = 0;
	temp->redir_output_append = 0;
	temp->my_func = 0;
	temp->next = NULL;
	return (temp);
}
