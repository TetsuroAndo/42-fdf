/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 06:18:11 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 08:40:18 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_iso_bounds
{
	double			min_x;
	double			max_x;
	double			min_y;
	double			max_y;
}					t_iso_bounds;

typedef struct s_point_calc
{
	size_t			grid_x;
	size_t			grid_y;
	double			world_x;
	double			world_y;
	double			world_z;
	double			iso_x;
	double			iso_y;
}					t_point_calc;

static void	initialize_iso_bounds(t_iso_bounds *bounds)
{
	bounds->min_x = 1000000000.0;
	bounds->max_x = -1000000000.0;
	bounds->min_y = 1000000000.0;
	bounds->max_y = -1000000000.0;
}

static void	update_iso_bounds(t_iso_bounds *bounds, double iso_x, double iso_y)
{
	if (iso_x < bounds->min_x)
		bounds->min_x = iso_x;
	if (iso_x > bounds->max_x)
		bounds->max_x = iso_x;
	if (iso_y < bounds->min_y)
		bounds->min_y = iso_y;
	if (iso_y > bounds->max_y)
		bounds->max_y = iso_y;
}

static t_iso_bounds	calculate_iso_bounds(t_fdf *fdf)
{
	t_point_calc	point;
	t_iso_bounds	bounds;
	double			pwz;

	initialize_iso_bounds(&bounds);
	point.grid_y = 0;
	while (point.grid_y < fdf->map.height)
	{
		point.grid_x = 0;
		while (point.grid_x < fdf->map.width)
		{
			pwz = (double)fdf->map.points[point.grid_y][point.grid_x].z;
			point.world_x = (double)point.grid_x;
			point.world_y = (double)point.grid_y;
			point.world_z = pwz;
			point.iso_x = (point.world_x - point.world_y) * cos(PI / 4);
			point.iso_y = (point.world_x + point.world_y) * sin(PI / 4)
				- point.world_z;
			update_iso_bounds(&bounds, point.iso_x, point.iso_y);
			point.grid_x++;
		}
		point.grid_y++;
	}
	return (bounds);
}

void	adjust_view(t_fdf *fdf)
{
	t_iso_bounds	iso_bounds;
	double			bounding_box_width;
	double			bounding_box_height;
	double			scale_factor_x;
	double			scale_factor_y;

	iso_bounds = calculate_iso_bounds(fdf);
	bounding_box_width = iso_bounds.max_x - iso_bounds.min_x;
	bounding_box_height = iso_bounds.max_y - iso_bounds.min_y;
	scale_factor_x = (double)fdf->window.width / bounding_box_width;
	scale_factor_y = (double)fdf->window.height / bounding_box_height;
	if (scale_factor_x < scale_factor_y)
		fdf->scale = (int)(scale_factor_x * 0.8);
	else
		fdf->scale = (int)(scale_factor_y * 0.8);
	fdf->shift_x = fdf->window.width / 2 - (int)(fdf->scale * ((iso_bounds.min_x
					+ iso_bounds.max_x) / 2.0));
	fdf->shift_y = fdf->window.height / 2 - (int)(fdf->scale
			* ((iso_bounds.min_y + iso_bounds.max_y) / 2.0));
}
