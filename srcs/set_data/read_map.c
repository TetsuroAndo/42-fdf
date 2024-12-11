/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:48:08 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 11:04:59 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_map_z_range(t_fdf *fdf, size_t y)
{
	size_t	x;

	x = 0;
	while (x < fdf->map.width)
	{
		if (fdf->map.points[y][x].z < fdf->map.min_z)
			fdf->map.min_z = fdf->map.points[y][x].z;
		if (fdf->map.points[y][x].z > fdf->map.max_z)
			fdf->map.max_z = fdf->map.points[y][x].z;
		x++;
	}
}

static void	parse_map_lines(int fd, t_fdf *fdf)
{
	char	*line;
	size_t	y;

	y = 0;
	line = get_next_line(fd);
	while (y < fdf->map.height && line != NULL)
	{
		parse_line(line, y, fdf);
		update_map_z_range(fdf, y);
		free(line);
		y++;
		line = get_next_line(fd);
	}
}

static t_map	init_map(char *file_name, t_fdf *fdf)
{
	t_map	map;
	int		fd;

	fd = open_file(file_name, fdf);
	parse_map_size(fd, fdf);
	close(fd);
	map.points = allocate_points(fdf);
	map.min_z = INT_MAX;
	map.max_z = INT_MIN;
	return (map);
}

t_map	read_map(char *file_name, t_fdf *fdf)
{
	t_map	map;
	int		fd;

	map = init_map(file_name, fdf);
	fdf->map = map;
	fd = open_file(file_name, fdf);
	parse_map_lines(fd, fdf);
	close(fd);
	return (fdf->map);
}
