/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:42:24 by teando            #+#    #+#             */
/*   Updated: 2024/12/10 05:33:50 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	swap_points(t_point *point1, t_point *point2)
{
	t_point	tmp;

	tmp = *point1;
	*point1 = *point2;
	*point2 = tmp;
}

static void	draw_line(t_fdf *fdf, t_point start, t_point end)
{
	if (ft_abs(end.y - start.y) < ft_abs(end.x - start.x))
	{
		if (start.x > end.x)
			swap_points(&start, &end);
		draw_line_low(fdf, start, end);
	}
	else
	{
		if (start.y > end.y)
			swap_points(&start, &end);
		draw_line_high(fdf, start, end);
	}
}

static void	draw_line_point(t_fdf *fdf, int x, int y, int next)
{
	t_point	start;
	t_point	end;

	start.x = x;
	start.y = y;
	isometric(fdf, &start.x, &start.y, fdf->map.points[y][x].z);
	if (next == 'h')
	{
		end.x = x + 1;
		end.y = y;
		isometric(fdf, &end.x, &end.y, fdf->map.points[y][x + 1].z);
	}
	else
	{
		end.x = x;
		end.y = y + 1;
		isometric(fdf, &end.x, &end.y, fdf->map.points[y + 1][x].z);
	}
	draw_line(fdf, start, end);
}

void	draw_map(t_fdf *fdf)
{
	size_t	x;
	size_t	y;

	fdf->shift_x = fdf->window.width / 2 - (fdf->map.width * fdf->scale) / 2;
	fdf->shift_y = fdf->window.height / 2 - (fdf->map.height * fdf->scale) / 2;
	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (x < fdf->map.width - 1)
				draw_line_point(fdf, (int)x, (int)y, 'h');
			if (y < fdf->map.height - 1)
				draw_line_point(fdf, (int)x, (int)y, 'v');
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->window.mlx_ptr, fdf->window.win_ptr,
		fdf->window.img_ptr, 0, 0);
}
