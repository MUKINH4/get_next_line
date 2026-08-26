/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaragat <smaragat@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 12:24:31 by smaragat          #+#    #+#             */
/*   Updated: 2026/08/24 12:24:31 by smaragat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strchr(char *str, char c)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	if (c == '\0')
		return (&str[i]);
	return (0);
}

char	*gnl_strjoin(char *str1, char *str2)
{
	char	*full_str;
	size_t	i;
	size_t	j;

	if (!str1 || !str2)
		return (NULL);
	i = 0;
	full_str = (char *)malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!full_str)
		return (NULL);
	while (str1[i])
	{
		full_str[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2[j])
		full_str[i++] = str2[j++];
	full_str[i] = '\0';
	free(str1);
	return (full_str);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	i = start;
	j = 0;
	while (i < ft_strlen((char *)s) && j < len)
		substr[j++] = s[i++];
	substr[j] = '\0';
	return (substr);
}

char	*gnl_remove_current_line(char *stored)
{
	char		*str;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (stored[i] && stored[i] != SEPARATOR)
		i++;
	if (!stored[i])
	{
		free(stored);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(stored) - i + 1));
	if (!str)
	{
		free(stored);
		return (NULL);
	}
	i++;
	while (stored[i])
		str[j++] = stored[i++];
	str[j] = '\0';
	free (stored);
	return (str);
}
