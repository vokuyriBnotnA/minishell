/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:27:04 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 09:08:10 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_variables	*init_var(void)
{
	t_variables	*lst;

	lst = (t_variables *) malloc(sizeof(t_variables));
	if (!lst)
		return (NULL);
	lst->name = NULL;
	lst->value = NULL;
	lst->next = NULL;
	return (lst);
}

t_variables	*add_var(t_variables *lst, char *name, char *value)
{
	t_variables	*temp;
	t_variables	*p;

	temp = (t_variables *) malloc(sizeof(t_variables));
	if (!temp)
		return (NULL);
	p = lst->next;
	lst->next = temp;
	temp->name = name;
	temp->value = value;
	return (temp);
}

char	*name_from_envp(char *envp)
{
	char	*name;
	int		i;

	name = malloc(ft_strlen_plus(envp, '=') + 1);
	if (!name)
		return (NULL);
	i = 0;
	while (*envp && *envp != '=')
	{
		name[i] = *envp;
		i++;
		envp++;
	}
	envp++;
	name[i] = 0;
	return (name);
}

t_variables	*take_var_from_envp(char *envp, t_variables	*lst)
{
	int		i;
	char	*name;
	char	*value;

	name = name_from_envp(envp);
	if (!name)
		return (NULL);
	value = malloc(ft_strlen(envp) + 1);
	if (!value)
		return (0);
	i = 0;
	while (envp[i])
	{
		value[i] = envp[i];
		i++;
	}
	value[i] = 0;
	lst = add_var(lst, name, value);
	return (lst);
}

int	variables_init(t_minishell *ms)
{
	int	i;

	i = 0;
	ms->var = init_var();
	if (!ms->var)
	{
		printf("minishell: Variables don't work\n");
		return (0);
	}
	ms->var_current = ms->var;
	while (ms->envp[i])
	{
		ms->var_current = take_var_from_envp(ms->envp[i], ms->var_current);
		if (!ms->var_current)
			return (0);
		i++;
	}
	return (1);
}
