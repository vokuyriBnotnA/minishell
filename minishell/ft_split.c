/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 05:46:32 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 01:43:35 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	words_count(char *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	if (str[0] != c)
		words++;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c && str[i + 1] != 0)
			words++;
		i++;
	}
	return (words);
}

static char	*start_word(char *str, char c)
{
	if (*str != c)
		return (str);
	while (*str == c && *str)
		str++;
	return (str);
	return (NULL);
}

char	**free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && *str[i])
			free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	return (NULL);
}

char	**ft_split_plus(char **res, char *str, char c, int words)
{
	int	i;
	int	j;

	i = 0;
	while (i < words)
	{
		j = 0;
		str = start_word(str, c);
		res[i] = malloc((ft_strlen_plus(str, c) + 1) * sizeof(char));
		if (!res[i])
			return (free_split(res));
		while (*str != c && *str)
		{
			res[i][j] = *str;
			str++;
			j++;
		}
		res[i][j] = 0;
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(char *str, char c)
{
	char	**res;
	int		words;

	if (!str)
		return (NULL);
	words = words_count(str, c);
	res = (char **) malloc((words + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res = ft_split_plus(res, str, c, words);
	if (!res)
		return (NULL);
	return (res);
}
