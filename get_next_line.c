/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaragat <smaragat@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 12:27:41 by smaragat          #+#    #+#             */
/*   Updated: 2026/08/24 12:27:41 by smaragat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_free(char  *stored, char *buffer)
{
	free(stored);
	free(buffer);
	return (NULL);
}

static char	*gnl_read(int fd, char *stored)
{
	ssize_t	i;
	char	*temp;

	if (!stored)
	{
		stored = malloc(1);
		if (!stored)
			return (NULL);
		stored[0] = '\0';
	}
	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	i = 1;
	while (!gnl_strchr(stored, SEPARATOR) && i > 0)
	{
		i = read(fd, temp, BUFFER_SIZE);
		if (i < 0)
			return (gnl_free(stored, temp));
		if (i == 0)
			break ;
		temp[i] = '\0';
		stored = gnl_strjoin(stored, temp);
	}
	free(temp);
	return (stored);
}

static char	*gnl_extract_current_line(char *stored)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!stored[i])
		return (NULL);
	while (stored[i] && stored[i] != SEPARATOR)
		i++;
	line = gnl_substr(stored, 0, i + (stored[i] == SEPARATOR));
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stored;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stored = gnl_read(fd, stored);
	if (!stored)
		return (NULL);
	line = gnl_extract_current_line(stored);
	stored = gnl_remove_current_line(stored);
	return (line);
}
