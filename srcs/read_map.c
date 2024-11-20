/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:42:31 by teando            #+#    #+#             */
/*   Updated: 2024/11/21 08:02:16 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <errno.h>
#include <string.h>

static int	open_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_error(strerror(errno));
	return (fd);
}

static void	parse_map_size(int fd, size_t *x, size_t *y)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		ft_error("Error: empty file or read error.");
	*x = ft_count_words(line, ' ');
	if (*x <= 0)
		ft_error("Error: Invalid map format.");
	while (line)
	{
		free(line);
		(*y)++;
		line = get_next_line(fd);
	}
	free(line);
}

static t_dot	**memory_allocete(char *file_name)
{
	t_dot	**new;
	int		fd;
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	fd = open_file(file_name);
	parse_map_size(fd, &x, &y);
	new = (t_dot **)malloc(sizeof(t_dot *) * (++y + 1));
	if (!new)
		ft_error("Error: Memory allocation failed.");
	while (y > 0)
	{
		new[--y] = (t_dot *)malloc(sizeof(t_dot) * (x + 1));
		if (!new[y])
			ft_error("Error: Memory allocation failed.");
	}
	close(fd);
	return (new);
}

static int	get_dots_from_line(char *line, t_dot **matrix_of_dots, size_t y)
{
	char	**dots;
	size_t	x;

	dots = ft_split(line, ' ');
	if (!dots)
		ft_error("Error: Memory allocation failed.");
	x = 0;
	while (dots[x])
	{
		matrix_of_dots[y][x].z = ft_atoi(dots[x]);
		matrix_of_dots[y][x].x = x;
		matrix_of_dots[y][x].y = y;
		matrix_of_dots[y][x].is_last = 0;
		free(dots[x++]);
	}
	free(dots);
	free(line);
	matrix_of_dots[y][--x].is_last = 1;
	return (x + 1);
}

t_dot	**read_map(char *file_name)
{
	t_dot	**matrix_of_dots;
	size_t	y;
	int		fd;
	char	*line;
	int		expected_x;

	matrix_of_dots = memory_allocete(file_name);
	y = 0;
	fd = open_file(file_name);
	line = get_next_line(fd);
	expected_x = get_dots_from_line(line, matrix_of_dots, y++);
	while (line)
	{
		if (get_dots_from_line(line, matrix_of_dots, y++) != expected_x)
			ft_error("Error: Map width does not match");
		line = get_next_line(fd);
	}
	free(line);
	matrix_of_dots[y] = NULL;
	close(fd);
	return (matrix_of_dots);
}
