/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:22:45 by teando            #+#    #+#             */
/*   Updated: 2024/12/12 11:38:43 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point2d	iso_transform_2d(t_point3d in_p)
{
	t_point2d	out;
	double		angle;
	double		cos_a;
	double		sin_a;

	angle = M_PI / 6.0;
	cos_a = cos(angle);
	sin_a = sin(angle);
	out.x = (in_p.x - in_p.y) * cos_a;
	out.y = (in_p.x + in_p.y) * sin_a - in_p.z;
	return (out);
}

static void	isometric(t_fdf *fdf, int *x, int *y, int z)
{
	t_point3d	p3d;
	t_point2d	p2d;

	p3d.x = (double)*x;
	p3d.y = (double)*y;
	p3d.z = (double)z * fdf->z_scale;
	p2d = iso_transform_2d(p3d);
	*x = (int)(p2d.x * fdf->scale + fdf->shift_x);
	*y = (int)(p2d.y * fdf->scale + fdf->shift_y);
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
