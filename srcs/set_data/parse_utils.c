/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:13:04 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 18:54:01 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**allocate_points(t_fdf *fdf, size_t height, size_t width)
{
	t_point	**points;
	size_t	i;

	points = (t_point **)malloc(sizeof(t_point *) * (height + 1));
	if (!points)
		ft_error("Error: Memory allocation failed", fdf);
	i = 0;
	while (i < height)
	{
		points[i] = (t_point *)malloc(sizeof(t_point) * width);
		if (!points[i])
		{
			points[i] = NULL;
			free_2d_points(points, 0);
			ft_error("Error: Memory allocation failed", fdf);
		}
		i++;
	}
	points[i] = NULL;
	return (points);
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

static void	parse_z_color(char *val, int *z, int *color)
{
	char	*comma;
	char	*hex;

	comma = ft_strchr(val, ',');
	*color = DEFAULT_COLOR;
	if (comma)
	{
		*comma = '\0';
		*z = ft_atoi(val);
		hex = comma + 1;
		if (ft_strnstr(hex, "0x", 2))
			hex += 2;
		*color = (int)ft_strtol(hex, NULL, 16);
	}
	else
		*z = ft_atoi(val);
}

void	parse_line(char *line, size_t y, t_fdf *fdf)
{
	char	**values;
	t_point	*points;
	size_t	x;
	int		z;
	int		color;

	points = fdf->map.points[y];
	values = ft_split(line, ' ');
	if (!values)
		ft_error("Error: Split failed", fdf);
	x = 0;
	while (x < fdf->map.width && values[x])
	{
		parse_z_color(values[x], &z, &color);
		points[x].x = (int)x;
		points[x].y = (int)y;
		points[x].z = z;
		points[x].color = color;
		x++;
	}
	free_2d_char(values);
}
