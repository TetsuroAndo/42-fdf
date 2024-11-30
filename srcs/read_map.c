/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:42:31 by teando            #+#    #+#             */
/*   Updated: 2024/11/27 21:15:52 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "fdf.h"

static void parse_map_size(int fd, size_t *width, size_t *height)
{
	char *line;
	size_t line_width;
	size_t min_width;

	*height = 0;
	min_width = SIZE_MAX;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_width = ft_count_words(line, ' ');
		if (line_width < min_width)
			min_width = line_width;
		free(line);
		(*height)++;
		line = get_next_line(fd);
	}
	*width = min_width;
	if (*width == 0 || *height == 0)
		ft_error("Error: Invalid map size");
}

static t_point **allocate_points(size_t width, size_t height)
{
	t_point **points;
	size_t i;

	points = (t_point **)malloc(sizeof(t_point *) * height);
	if (!points)
		ft_error("Error: Memory allocation failed");
	i = 0;
	while (i < height)
	{
		points[i] = (t_point *)malloc(sizeof(t_point) * width);
		if (!points[i])
		{
			while (i > 0)
				free(points[--i]);
			free(points);
			ft_error("Error: Memory allocation failed");
		}
		i++;
	}
	return (points);
}

static void parse_line(char *line, t_point *points, size_t width, size_t y)
{
	char **values;
	size_t x;
	char *z_str;

	values = ft_split(line, ' ');
	if (!values)
		ft_error("Error: Split failed");
	x = -1;
	while (++x < width && values[x])
	{
		points[x].x = x;
		points[x].y = y;
		if (ft_strchr(values[x], ','))
			z_str = ft_strndup(values[x], ft_strchr(values[x], ',') - values[x]);
		else
			z_str = ft_strdup(values[x]);
		points[x].z = ft_atoi(z_str);
		free(z_str);
		points[x].color = parse_color(values[x]);
	}
	x = 0;
	while (values[x])
		free(values[x++]);
	free(values);
}

static void find_z_range(t_map *map)
{
	size_t x;
	size_t y;

	map->min_z = INT_MAX;
	map->max_z = INT_MIN;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->points[y][x].z < map->min_z)
				map->min_z = map->points[y][x].z;
			if (map->points[y][x].z > map->max_z)
				map->max_z = map->points[y][x].z;
		}
	}
}

static void apply_default_colors(t_map *map)
{
	size_t x;
	size_t y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->points[y][x].color == -1)
				map->points[y][x].color = get_default_color(
					map->points[y][x].z, map->min_z, map->max_z);
		}
	}
}

t_map read_map(char *file_name)
{
	t_map map;
	int fd;
	char *line;
	size_t y;

	fd = open_file(file_name);
	parse_map_size(fd, &map.width, &map.height);
	close(fd);
	map.points = allocate_points(map.width, map.height);
	fd = open_file(file_name);
	line = get_next_line(fd);
	y = 0;
	while (y < map.height && line != NULL)
	{
		parse_line(line, map.points[y], map.width, y);
		free(line);
		y++;
		line = get_next_line(fd);
	}
	close(fd);
	find_z_range(&map);
	apply_default_colors(&map);
	return (map);
}
