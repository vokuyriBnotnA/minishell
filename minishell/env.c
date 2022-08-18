/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 04:06:18 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 04:09:39 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_ms(t_minishell *ms)
{
	ms->var_current = ms->var->next;
	while (ms->var_current != NULL)
	{
		printf("%s=%s\n", ms->var_current->name, ms->var_current->value);
		ms->var_current = ms->var_current->next;
	}
	return (1);
}
