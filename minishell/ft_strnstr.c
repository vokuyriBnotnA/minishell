/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 05:45:00 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/27 23:53:29 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnstr(char *haystack, char *needle, int len)
{
	int	i;

	i = 0;
	if (!haystack[i] || !haystack || !needle || !needle[i])
		return (NULL);
	while (haystack[i] && needle[i] && haystack[i] == needle[i] && i < len)
		i++;
	if (i == len)
		return (&haystack[i - len]);
	else
		return (ft_strnstr(&haystack[i + 1], needle, len));
}
