/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:13:04 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 11:04:42 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_free_list(char **ptr)
{
	size_t	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

void	parse_map_size(int fd, t_fdf *fdf)
{
	char	*line;
	size_t	line_width;
	size_t	min_width;
	size_t	line_count;

	min_width = SIZE_MAX;
	line_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		line_width = ft_count_words(line, ' ');
		if (line_width < min_width)
			min_width = line_width;
		free(line);
		line_count++;
		line = get_next_line(fd);
	}
	fdf->map.width = min_width;
	fdf->map.height = line_count;
	if (fdf->map.width == 0 || fdf->map.height == 0)
		ft_error("Error: Invalid map size", fdf);
}

t_point	**allocate_points(t_fdf *fdf)
{
	t_point	**points;
	size_t	i;

	points = (t_point **)malloc(sizeof(t_point *) * fdf->map.height);
	if (!points)
		ft_error("Error: Memory allocation failed", fdf);
	i = 0;
	while (i < fdf->map.height)
	{
		points[i] = (t_point *)malloc(sizeof(t_point) * fdf->map.width);
		if (!points[i])
		{
			while (i > 0)
				free(points[--i]);
			free(points);
			ft_error("Error: Memory allocation failed", fdf);
		}
		i++;
	}
	return (points);
}

void	parse_line(char *line, size_t y, t_fdf *fdf)
{
	char	**values;
	size_t	x;
	size_t	width;
	t_point	*points;

	width = fdf->map.width;
	points = fdf->map.points[y];
	values = ft_split(line, ' ');
	if (!values)
		ft_error("Error: Split failed", fdf);
	x = 0;
	while (x < width && values[x])
	{
		points[x].x = (int)x;
		points[x].y = (int)y;
		points[x].z = ft_atoi(values[x]);
		x++;
	}
	ft_free_list(values);
}
