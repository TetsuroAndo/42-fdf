/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:22:45 by teando            #+#    #+#             */
/*   Updated: 2024/12/12 11:29:26 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	isometric(t_fdf *fdf, int *x, int *y, int z)
{
	double	angle;
	double	cos_a;
	double	sin_a;
	double	x_iso;
	double	y_iso;

	angle = M_PI / 6.0;
	cos_a = cos(angle);
	sin_a = sin(angle);
	x_iso = ((double)*x - (double)*y) * cos_a;
	y_iso = ((double)*x + (double)*y) * sin_a - (double)z * fdf->z_scale;
	*x = (int)(x_iso * fdf->scale + fdf->shift_x);
	*y = (int)(y_iso * fdf->scale + fdf->shift_y);
}

void	project_points(t_fdf *fdf)
{
	size_t	y;
	size_t	x;

	if (fdf->projected)
		free_2d_points(fdf->projected, fdf->map.height);
	fdf->projected = allocate_points(fdf, fdf->map.height, fdf->map.width);
	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			fdf->projected[y][x].x = (int)x;
			fdf->projected[y][x].y = (int)y;
			fdf->projected[y][x].z = fdf->map.points[y][x].z;
			fdf->projected[y][x].color = fdf->map.points[y][x].color;
			isometric(fdf, &fdf->projected[y][x].x, &fdf->projected[y][x].y,
				fdf->projected[y][x].z);
			x++;
		}
		y++;
	}
}
