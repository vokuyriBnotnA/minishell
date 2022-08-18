/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:32:20 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 08:59:27 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	redir_type(t_minishell *ms, char *cmd, int *count)
{
	if (cmd[0] == '<' && cmd[1] == '>')
	{
		printf("minishell: Wrong redirections\n");
		return (0);
	}
	if (cmd[0] == '<' && cmd[1] == '<')
	{
		ms->commands_current->here_doc_flag = "stop";
		count[0]++;
	}
	if (cmd[0] == '>' && cmd[1] == '>')
	{
		ms->commands_current->redir_output_append = 1;
		count[0]++;
	}
	count[0]++;
	return (cmd[0]);
}

int	redir_name(t_minishell *ms, char *cmd, int *i)
{
	char	type_redir;

	type_redir = redir_type(ms, &cmd[*i], i);
	while (*i < ft_strlen(cmd) && cmd[*i] == ' ')
		i[0]++;
	if (!redirections(ms, &cmd[*i], i, type_redir))
		return (0);
	while (*i < ft_strlen(cmd) && cmd[*i] == ' ')
		i[0]++;
	return (1);
}

int	cmd_name(t_minishell *ms, char *cmd, int *i, int *cmd_count)
{
	cmd_count[0]++;
	if (!excerpt_cmd(ms, &cmd[*i], i))
		return (0);
	while (*i < ft_strlen(cmd) && cmd[*i] == ' ')
		i[0]++;
	return (1);
}

int	further_process_cmd(t_minishell *ms, char *cmd)
{
	int		i;
	int		cmd_count;

	i = 0;
	cmd_count = 0;
	while (i < ft_strlen(cmd) && cmd[i] == ' ')
		i++;
	while (i < ft_strlen(cmd))
	{
		if (cmd[i] == '<' || cmd[i] == '>')
			if (!redir_name(ms, cmd, &i))
				return (0);
		if (cmd[i] != '<' && cmd[i] != '>' && cmd[i] != ' '
			&& i < ft_strlen(cmd))
			if (!cmd_name(ms, cmd, &i, &cmd_count))
				return (0);
		if (cmd_count > 1)
		{
			printf("minishell: Wrong cmd: %s\n", cmd);
			return (0);
		}
	}
	ms->pipe_count++;
	ms->commands_current = add_commands(ms->commands_current);
	return (1);
}

int	parsing(t_minishell *ms)
{
	int		i;
	char	*cmd_to_pipe;
	char	quotes;

	i = 0;
	quotes = 0;
	ms->commands_current = ms->commands;
	while (i < ft_strlen(ms->cmd))
	{
		cmd_to_pipe = malloc(ft_strlen(&ms->cmd[i]) + 1);
		if (!cmd_to_pipe)
			return (0);
		parsing_2(ms, cmd_to_pipe, &i, &quotes);
		if (!parsing_3(ms, cmd_to_pipe))
			return (0);
		i++;
	}
	return (1);
}
