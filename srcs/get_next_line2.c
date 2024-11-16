/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:08:47 by teando            #+#    #+#             */
/*   Updated: 2024/11/16 23:33:28 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static ssize_t	read_newline(char **r, char **newline, int fd)
{
    ssize_t read_total;
    ssize_t size;
    char	*buf;
    char	*tmp;

    buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buf)
        return (free(*r), -1);
    read_total = 0;
    while (!*newline)
    {
        size = read(fd, buf, BUFFER_SIZE);
        if (size <= 0)
            return (free(buf), size);
        buf[size] = '\0';
        read_total += size;
        tmp = ft_strjoin(*r, buf);
        if (!tmp)
            return (free(buf), -1);
        free(*r);
        *r = tmp;
        *newline = ft_strchr(*r + (read_total - BUFFER_SIZE - 1), '\n');
    }
    return (free(buf), read_total);
}

static ssize_t	str_partitioning(char **r, char **newline, char **saved, int fd)
{
	char	*tmp;

    *saved = ft_strdup(*newline + 1);
    if (!*saved)
        return (free(*r), -1);
    tmp = ft_strndup(*r, *newline - *r + 1);
    free(*r);
    if (!tmp)
        return (free(*saved), -1);
    *r = tmp;
    return (1);
}


char	*get_next_line(int fd)
{
	static char	*saved;
	char		*newline;
	char		*r;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (saved)
        newline = ft_strchr(saved, '\n');
    else
        newline = NULL;
    r = saved;
    if (read_newline(r, newline, fd) <= 0)
        return (free(r), NULL);
    if (str_partitioning(&r, &newline, &saved, fd) == -1)
    {
        return (free(r), NULL);
    }
    return (r);
}
