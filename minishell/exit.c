/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 04:03:08 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 04:34:10 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_ms(char *num)
{
	int	i;

	i = 0;
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
		{
			printf("minishell: exit: %s: numeric argument required\n", num);
			return ;
		}
		i++;
	}
	printf("%s\n", num);
	exit(1);
}
