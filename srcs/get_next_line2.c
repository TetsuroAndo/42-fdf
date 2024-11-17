/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:08:47 by teando            #+#    #+#             */
/*   Updated: 2024/11/17 15:24:54 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static ssize_t	read_buf_to_newline(char **r, char **newline, int fd)
{
    ssize_t read_total;
    ssize_t size;
    char	*buf;
    
    buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buf)
        return (-1);
    read_total = 0;
    while (!*newline)
    {
        size = read(fd, buf, BUFFER_SIZE);
        if (size <= 0)
            return (free(buf), size);
        buf[size] = '\0';
        read_total += size;
        *r = ft_realloc(*r, read_total + 1);
        if (!*r)
            return (free(buf), -1);
        ft_strlcat(*r, buf, read_total + 1);
        *newline = ft_strchr(*r + (read_total - size - 1), '\n');
    }
    return (free(buf), read_total);
}

static ssize_t	str_partitioning(char **r, char **newline, char **saved, int fd)
{
    *saved = ft_strdup(*newline + 1);
    if (!*saved)
        return (free(*r), -1);
    (*r)[*newline - *r + 1] = '\0';
    return (1);
}


char	*get_next_line(int fd)
{
	static char	*saved;
	char		*newline;
	char		*r;
    ssize_t     read_size;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (saved)
        newline = ft_strchr(saved, '\n');
    else
        newline = NULL;
    r = saved;
    if (!newline)
    {
        read_size = read_buf_to_newline(r, newline, fd);
        if (read_size == -1)
            return (free(r), NULL);
        if (read_size == 0)
            saved = NULL;
    }
    if (newline)
        if (str_partitioning(&r, &newline, &saved, fd) == -1)
            return (free(r), NULL);
    return (r);
}
