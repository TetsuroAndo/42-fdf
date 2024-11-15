/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 07:10:16 by teando            #+#    #+#             */
/*   Updated: 2024/11/16 06:02:07 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*endfree_strndup(const char *s, size_t n)
{
	char	*r;
	char	*r_head;
	char	*s_head;
	size_t	len;

	len = 0;
	while (len < n && s[len])
		len++;
	s_head = (char *)s;
	r_head = (char *)malloc((len + 1) * sizeof(char));
	if (r_head)
	{
		r = r_head;
		while (len--)
			*r++ = *s++;
		*r = '\0';
		free(s_head);
	}
	return (r_head);
}

static ssize_t	read_buf(char **buf, int fd)
{
	ssize_t	size;

	*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*buf)
		return (-1);
	size = read(fd, *buf, BUFFER_SIZE);
	if (size <= 0)
	{
		free(*buf);
		*buf = NULL;
		return (size);
	}
	(*buf)[size] = '\0';
	return (size);
}

static ssize_t	fetch_one_line(char **r, char **newline, char **saved, int fd)
{
	char	*buf;
	char	*tmp;
	ssize_t	code;

	while (!*newline)
	{
		code = read_buf(&buf, fd);
		if (code <= 0)
			return (code);
		tmp = ft_strjoin(*r, buf);
		free(buf);
		if (!tmp)
			return (-1);
		free(*r);
		*r = tmp;
		*newline = ft_strchr(*r, '\n');
	}
	*saved = ft_strdup(*newline + 1);
	if (!*saved)
		return (-1);
	tmp = endfree_strndup(*r, *newline - *r + 1);
	if (!tmp)
		return (-1);
	*r = tmp;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*newline;
	char		*r;
	ssize_t		code;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (saved)
		newline = ft_strchr(saved, '\n');
	else
		newline = NULL;
	r = saved;
	code = fetch_one_line(&r, &newline, &saved, fd);
	if (code <= 0 && r && *r)
	{
		if (code == -1 && saved != r)
			free(saved);
		saved = NULL;
	}
	if (code == -1 || (r && !*r))
	{
		free(r);
		r = NULL;
	}
	return (r);
}
