/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaragat <smaragat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 15:38:32 by smaragat          #+#    #+#             */
/*   Updated: 2026/08/26 15:38:44 by smaragat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef SEPARATOR
#  define SEPARATOR '\n'
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);

size_t	ft_strlen(char *str);
char	*gnl_strjoin(char *str1, char *str2);
char	*gnl_strchr(char *str, char c);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_remove_current_line(char *stored);

#endif
