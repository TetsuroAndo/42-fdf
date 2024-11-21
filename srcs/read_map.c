/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:42:31 by teando            #+#    #+#             */
/*   Updated: 2024/11/21 13:07:00 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	error_cleanup_memory(char *msg, t_dot **matrix, size_t y, int fd)
{
	if (fd > 2)
		close(fd);
	while (y > 0)
		free(matrix[--y]);
	if (matrix)
		free(matrix);
	ft_error(msg);
}

static void	parse_map_size(int fd, size_t *x, size_t *y)
{
	char	*line;
	size_t	sml_x;

	*x = 0;
	*y = 0;
	sml_x = INT_MAX;
	line = get_next_line(fd);
	if (!line)
		ft_error("Error: empty file or read error.");
	while (line)
	{
		*x = ft_count_words(line, ' ');
		if (*x < sml_x)
			sml_x = *x;
		free(line);
		(*y)++;
		line = get_next_line(fd);
	}
	*x = sml_x;
}

static t_dot	**memory_allocate(char *file_name, size_t *x, size_t *y)
{
	t_dot	**new;
	int		fd;
	size_t	i;

	fd = open_file(file_name);
	parse_map_size(fd, x, y);
	new = (t_dot **)malloc(sizeof(t_dot *) * (*y + 1));
	if (!new)
		error_cleanup_memory("Error: Memory allocation failed.", NULL, 0, fd);
	i = -1;
	while (++i < *y)
	{
		new[i] = (t_dot *)malloc(sizeof(t_dot) * (*x + 1));
		if (!new[i])
			error_cleanup_memory("Error: Memory allocation failed.", new, i,
				fd);
	}
	close(fd);
	return (new);
}

static int	get_dots_from_line(char *line, t_dot **matrix_of_dots, size_t y,
		size_t max_x)
{
	char	**dots;
	size_t	x;

	if (!line || !matrix_of_dots)
		return (1);
	dots = ft_split(line, ' ');
	if (!dots)
		return (free(line), 0);
	x = 0;
	while (dots[x])
	{
		if (x < max_x)
		{
			matrix_of_dots[y][x].z = ft_atoi(dots[x]);
			matrix_of_dots[y][x].x = x;
			matrix_of_dots[y][x].y = y;
			matrix_of_dots[y][x].is_last = 0;
		}
		free(dots[x++]);
	}
	matrix_of_dots[y][--x].is_last = 1;
	free(dots);
	free(line);
	return (x + 1);
}

t_dot	**read_map(char *file_name)
{
	t_dot	**matrix_of_dots;
	size_t	x;
	size_t	y;
	size_t	i;
	int		fd;
	char	*read_line;
	int		expected_x;

	matrix_of_dots = memory_allocate(file_name, &x, &y);
	fd = open_file(file_name);
	read_line = get_next_line(fd);
	i = -1;
	while (read_line && ++i < y)
	{
		if (!get_dots_from_line(read_line, matrix_of_dots, i, x))
			error_cleanup_memory("Error: Map width does not match",
				matrix_of_dots, y, fd);
		read_line = get_next_line(fd);
	}
	matrix_of_dots[y] = NULL;
	close(fd);
	return (matrix_of_dots);
}
