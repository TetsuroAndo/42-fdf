/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:42:31 by teando            #+#    #+#             */
/*   Updated: 2024/12/10 06:41:20 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_map_z_range(t_map *map, size_t y)
{
	size_t	x;

	x = 0;
	while (x < map->width)
	{
		if (map->points[y][x].z < map->min_z)
			map->min_z = map->points[y][x].z;
		if (map->points[y][x].z > map->max_z)
			map->max_z = map->points[y][x].z;
		x++;
	}
}

static void	parse_map_lines(int fd, t_map *map)
{
	char	*line;
	size_t	y;

	y = 0;
	line = get_next_line(fd);
	while (y < map->height && line != NULL)
	{
		parse_line(line, map->points[y], map->width, y);
		update_map_z_range(map, y);
		free(line);
		y++;
		line = get_next_line(fd);
	}
}

static t_map	init_map(char *file_name)
{
	t_map	map;
	int		fd;

	fd = open_file(file_name);
	parse_map_size(fd, &map.width, &map.height);
	close(fd);
	map.points = allocate_points(map.width, map.height);
	map.min_z = INT_MAX;
	map.max_z = INT_MIN;
	return (map);
}

t_map	read_map(char *file_name)
{
	t_map	map;
	int		fd;

	map = init_map(file_name);
	fd = open_file(file_name);
	parse_map_lines(fd, &map);
	close(fd);
	return (map);
}
