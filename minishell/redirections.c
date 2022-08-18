/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:06:14 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 10:34:31 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirections(t_minishell *ms, char *cmd, int *count, char type)
{
	char	*name;
	int		i;

	name = malloc(ft_strlen(cmd));
	i = 0;
	while (i < ft_strlen(cmd) && cmd[i] != ' ')
	{
		name[i] = cmd[i];
		i++;
	}
	name[i] = 0;
	*count += i;
	if (open_file(ms, name, type) != 2)
		free(name);
	return (1);
}
