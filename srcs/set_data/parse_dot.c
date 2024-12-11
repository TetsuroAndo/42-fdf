/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:13:04 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 10:36:06 by teando           ###   ########.fr       */
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

void	parse_map_size(int fd, size_t *width, size_t *height)
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
	*width = min_width;
	*height = line_count;
	if (*width == 0 || *height == 0)
		ft_error("Error: Invalid map size");
}

t_point	**allocate_points(size_t width, size_t height)
{
	t_point	**points;
	size_t	i;

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

void	parse_line(char *line, t_point *points, size_t width, size_t y)
{
	char	**values;
	size_t	x;

	values = ft_split(line, ' ');
	x = 0;
	if (!values)
		ft_error("Error: Split failed", NULL);
	while (x < width && values[x])
	{
		points[x].x = (int)x;
		points[x].y = (int)y;
		points[x].z = ft_atoi(values[x]);
		x++;
	}
	ft_free_list(values);
}
