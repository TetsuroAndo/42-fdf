/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:22:45 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 09:57:10 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_projected(t_fdf *fdf)
{
	size_t	y;

	y = 0;
	while (y < fdf->map.height)
	{
		free(fdf->projected[y]);
		y++;
	}
	free(fdf->projected);
}

static void	isometric(t_fdf *fdf, int *x, int *y, int z)
{
	double	angle;
	double	cos_a;
	double	sin_a;
	double	dx;
	double	dy;

	dx = (double)*x;
	dy = (double)*y;
	angle = M_PI / 4.0;
	cos_a = cos(angle);
	sin_a = sin(angle);
	dx = (dx - dy) * cos_a;
	dy = ((double)*x + (double)*y) * sin_a - (double)z * fdf->z_scale;
	dx = dx * fdf->scale + fdf->shift_x;
	dy = dy * fdf->scale + fdf->shift_y;
	*x = (int)dx;
	*y = (int)dy;
}

static void	allocate_projected(t_fdf *fdf)
{
	size_t	y;

	fdf->projected = (t_point **)malloc(sizeof(t_point *) * fdf->map.height);
	if (!fdf->projected)
		ft_error("Failed to allocate memory for projected points");
	y = 0;
	while (y < fdf->map.height)
	{
		fdf->projected[y] = (t_point *)malloc(sizeof(t_point) * fdf->map.width);
		if (!fdf->projected[y])
			ft_error("Failed to allocate memory for projected row");
		y++;
	}
}

void	project_points(t_fdf *fdf)
{
	size_t	y;
	size_t	x;

	if (fdf->projected)
		free_projected(fdf);
	allocate_projected(fdf);
	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			fdf->projected[y][x].x = x;
			fdf->projected[y][x].y = y;
			fdf->projected[y][x].z = fdf->map.points[y][x].z;
			isometric(fdf, &fdf->projected[y][x].x, &fdf->projected[y][x].y,
				fdf->projected[y][x].z);
			x++;
		}
		y++;
	}
}
