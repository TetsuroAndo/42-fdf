/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:22:45 by teando            #+#    #+#             */
/*   Updated: 2024/12/12 13:30:07 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point3d	rotate_point(t_point3d p, double rx, double ry, double rz)
{
	t_point3d	tmp;

	// 回転X軸
	tmp.x = p.x;
	tmp.y = p.y * cos(rx) - p.z * sin(rx);
	tmp.z = p.y * sin(rx) + p.z * cos(rx);
	// 回転Y軸
	p.x = tmp.x * cos(ry) + tmp.z * sin(ry);
	p.y = tmp.y;
	p.z = -tmp.x * sin(ry) + tmp.z * cos(ry);
	// 回転Z軸
	tmp.x = p.x * cos(rz) - p.y * sin(rz);
	tmp.y = p.x * sin(rz) + p.y * cos(rz);
	tmp.z = p.z;
	return (tmp);
}

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

t_point2d	parallel_transform_2d(t_point3d in_p)
{
	t_point2d	out;

	out.x = in_p.x;
	out.y = in_p.y;
	return (out);
}

void	project_points(t_fdf *fdf)
{
	size_t		y;
	size_t		x;
	t_point3d	p3d;
	t_point2d	p2d;

	if (fdf->projected)
		free_2d_points(fdf->projected, fdf->map.height);
	fdf->projected = allocate_points(fdf, fdf->map.height, fdf->map.width);
	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			p3d.x = (double)x;
			p3d.y = (double)y;
			p3d.z = (double)fdf->map.points[y][x].z * fdf->z_scale;
			p3d = rotate_point(p3d, fdf->rot_x, fdf->rot_y, fdf->rot_z);
			if (fdf->projection_mode == ISO)
				p2d = iso_transform_2d(p3d);
			else
				p2d = parallel_transform_2d(p3d);
			fdf->projected[y][x].x = (int)(p2d.x * fdf->scale + fdf->shift_x);
			fdf->projected[y][x].y = (int)(p2d.y * fdf->scale + fdf->shift_y);
			fdf->projected[y][x].z = fdf->map.points[y][x].z;
			fdf->projected[y][x].color = fdf->map.points[y][x].color;
			x++;
		}
		y++;
	}
}
