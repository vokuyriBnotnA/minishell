/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 13:34:14 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/27 16:24:16 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strdup(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = 0;
	if (s1[0] != 0)
		free(s1);
	return (res);
}

static char	*get_last_line(char *s, int i, char *res)
{
	if (s[0] != 0 && BUFFER_SIZE > 0)
	{
		s[i] = 0;
		res = ft_strdup(res, s);
		s[0] = 0;
		return (res);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	s[BUFFER_SIZE + 1];
	char		*res;
	int			i;

	i = 0;
	res = "";
	s[0] = 0;
	while (read(fd, &s[i], 1) && i <= BUFFER_SIZE && BUFFER_SIZE > 0 && fd >= 0
		&& (fd < 100 || BUFFER_SIZE < 1000) && s[i] != 0)
	{
		if ((i + 1) == BUFFER_SIZE && s[i] != '\n' && s[i] != 0)
		{
			s[i + 1] = 0;
			res = ft_strdup(res, s);
			i = -1;
		}
		if (s[i] == '\n')
		{
			s[i + 1] = 0;
			res = ft_strdup(res, s);
			return (res);
		}
		i++;
	}
	return (get_last_line(s, i, res));
}
