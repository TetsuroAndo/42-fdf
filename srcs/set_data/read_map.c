/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:42:31 by teando            #+#    #+#             */
/*   Updated: 2024/12/10 05:39:14 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	read_map(char *file_name)
{
	t_map	map;
	int		fd;
	char	*line;
	size_t	y;

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
	map.min_z = 0;
	map.max_z = 0;
	return (map);
}
