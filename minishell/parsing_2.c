/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 08:58:43 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 08:59:30 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_3(t_minishell *ms, char *cmd_to_pipe)
{
	if (cmd_to_pipe && *cmd_to_pipe)
	{
		if (!further_process_cmd(ms, cmd_to_pipe))
		{
			free(cmd_to_pipe);
			return (0);
		}
	}
	free(cmd_to_pipe);
	cmd_to_pipe = NULL;
	return (1);
}

int	parsing_2(t_minishell *ms, char *cmd_to_pipe, int *i, char *quotes)
{
	int	j;

	j = 0;
	while (ms->cmd[*i] && ((ms->cmd[*i] != '|' && !quotes[0])
			|| (ms->cmd[*i] != quotes[0] && quotes[0])))
	{
		if (ms->cmd[*i] == '\"' || ms->cmd[*i] == '\'')
		{
			*quotes = ms->cmd[*i];
			i[0]++;
		}
		cmd_to_pipe[j] = ms->cmd[*i];
		j++;
		i[0]++;
	}
	cmd_to_pipe[j] = 0;
	return (1);
}
