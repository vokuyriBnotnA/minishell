/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:04:22 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 11:35:49 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_ms(t_minishell *ms, int argc, char **argv, char **envp)
{
	ms->argc = argc;
	ms->argv = argv;
	ms->envp = envp;
	ms->path = malloc(1000);
	if (!ms->path)
		return (0);
	getcwd(ms->path, 999);
	g_exit_code = "0";
	if (!history_init(ms) || !variables_init(ms))
		return (0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;

	if (!init_ms(&ms, argc, argv, envp))
		return (1);
	if (!read_cmd(&ms))
		return (1);
	free_ms_var(&ms);
	return (0);
}
