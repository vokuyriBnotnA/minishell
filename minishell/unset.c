/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 01:52:58 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 05:36:58 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_minishell *ms, char *var_name)
{
	ms->var_current = ms->var;
	while (ms->var_current != NULL)
	{
		if (ms->var_current->name)
		{
			if (compare_str(var_name, ms->var_current->name, \
			ft_strlen(var_name)) && ms->var_current->value)
			{
				ms->var_current->value[0] = ' ';
				ms->var_current->value[1] = 0;
				return ;
			}
		}
		ms->var_current = ms->var_current->next;
	}
}
