/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excerpt_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:07:02 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 07:34:43 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_name(char *cmd, int *count)
{
	int		i;
	char	*name;

	i = 0;
	name = malloc(ft_strlen(cmd) + 1);
	while (cmd[i] && cmd[i] != ' ')
	{
		name[i] = cmd[i];
		i++;
	}
	name[i] = 0;
	*count += i;
	return (name);
}

char	*question(char *name, int *count, int *j)
{
	free(name);
	*count += 1;
	*j += ft_strlen(g_exit_code);
	return (g_exit_code);
}

char	*return_var(t_minishell *ms, char *cmd, int *count, int *j)
{
	char	*name;
	int		i;

	name = var_name(cmd, count);
	if (name[0] == '?' && ft_strlen(name) == 1)
		return (question(name, count, j));
	ms->var_current = ms->var;
	while (ms->var_current != NULL)
	{
		i = 0;
		if (ms->var_current->name)
		{
			if (compare_str(name, ms->var_current->name, ft_strlen(name))
				&& ms->var_current->value)
			{
				free(name);
				*j += ft_strlen(ms->var_current->value);
				return (ms->var_current->value);
			}
		}
		ms->var_current = ms->var_current->next;
	}
	free(name);
	return (" ");
}

int	excerpt_cmd(t_minishell *ms, char *cmd, int *count)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ms->commands_current->cmd = malloc(ft_strlen(cmd) + 1);
	while (i < ft_strlen(cmd) && cmd[i] != '<' && cmd[i] != '>')
	{
		if (cmd[i] == '$' && cmd[i + 1] != ' ')
		{
			i++;
			tmp = ms->commands_current->cmd;
			ms->commands_current->cmd = ft_strjoin(tmp, \
			return_var(ms, &cmd[i], &i, &j));
			free(tmp);
		}
		ms->commands_current->cmd[j] = cmd[i];
		j++;
		i++;
	}
	ms->commands_current->cmd[j] = 0;
	*count += i;
	return (1);
}
