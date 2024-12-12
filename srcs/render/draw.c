/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:42:24 by teando            #+#    #+#             */
/*   Updated: 2024/12/12 11:44:42 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_line_data
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
}			t_line_data;

static void	init_line_data(t_line_data *data, t_point start, t_point end)
{
	data->dx = ft_abs(end.x - start.x);
	data->dy = -ft_abs(end.y - start.y);
	if (start.x < end.x)
		data->sx = 1;
	else
		data->sx = -1;
	if (start.y < end.y)
		data->sy = 1;
	else
		data->sy = -1;
	data->err = data->dx + data->dy;
}

static void	draw_line(t_fdf *fdf, t_point start, t_point end)
{
	t_line_data	data;
	int			e2;

	init_line_data(&data, start, end);
	while (1)
	{
		put_pixel(fdf, start.x, start.y, start.color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * data.err;
		if (e2 >= data.dy)
		{
			data.err += data.dy;
			start.x += data.sx;
		}
		if (e2 <= data.dx)
		{
			data.err += data.dx;
			start.y += data.sy;
		}
	}
}

void	draw_map(t_fdf *fdf)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (x < fdf->map.width - 1)
				draw_line(fdf, fdf->projected[y][x], fdf->projected[y][x + 1]);
			if (y < fdf->map.height - 1)
				draw_line(fdf, fdf->projected[y][x], fdf->projected[y + 1][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->window.mlx_ptr, fdf->window.win_ptr,
		fdf->window.img_ptr, 0, 0);
}
