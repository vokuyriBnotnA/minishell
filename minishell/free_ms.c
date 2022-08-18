/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:11:18 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 11:32:29 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_ms_var(t_minishell *ms)
{
	t_variables	*prev;

	ms->var_current = ms->var;
	while (ms->var_current != NULL)
	{
		prev = ms->var_current;
		if (prev->name && *prev->name)
			free(prev->name);
		if (prev->value && *prev->value)
			free(prev->value);
		free(prev);
		ms->var_current = ms->var_current->next;
	}
	free(ms->path);
	return (1);
}
