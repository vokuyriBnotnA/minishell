/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 02:32:23 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 05:32:47 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_my_func(char *str)
{
	if (compare_str(str, "unset", ft_strlen(str)))
		return (1);
	if (compare_str(str, "exit", ft_strlen(str)))
		return (1);
	if (compare_str(str, "cd", ft_strlen(str)))
		return (1);
	return (0);
}

int	is_my_func_child(char *str)
{
	if (compare_str(str, "env", ft_strlen(str)))
		return (1);
	if (compare_str(str, "export", ft_strlen(str)))
		return (1);
	return (0);
}

int	my_func(char *cmd_name, char **cmd, t_minishell *ms)
{
	if (compare_str(cmd_name, "unset", ft_strlen(cmd_name)))
	{
		if (!cmd[2])
		{
			unset(ms, cmd[1]);
			return (1);
		}
		return (0);
	}
	if (compare_str(cmd_name, "exit", ft_strlen(cmd_name)))
	{
		if (!cmd[2])
		{
			exit_ms(cmd[1]);
			return (1);
		}
		return (0);
	}
	if (compare_str(cmd_name, "cd", ft_strlen(cmd_name)))
	{
		if (!cmd[2])
			return (cd(cmd[1]));
		return (0);
	}
	return (1);
}

int	my_func_child(char *cmd_name, char **cmd, t_minishell *ms)
{
	if (compare_str(cmd_name, "env", ft_strlen(cmd_name)))
	{
		if (!cmd[1])
		{
			env_ms(ms);
			return (1);
		}
		return (0);
	}
	if (compare_str(cmd_name, "export", ft_strlen(cmd_name)))
	{
		if (!cmd[1])
		{
			export_ms(ms);
			return (1);
		}
		return (0);
	}
	return (1);
}
