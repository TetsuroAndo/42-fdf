/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 06:18:11 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 18:51:28 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <float.h>

typedef struct s_calc
{
	double			w;
	double			h;
	double			min_z;
	double			max_z;
	double			corners[8][3];
	double			min_x;
	double			max_x;
	double			min_y;
	double			max_y;
	double			box_w;
	double			box_h;
	double			scale_x;
	double			scale_y;
	double			scale;
}					t_calc;

typedef struct s_point3d
{
	double			x;
	double			y;
	double			z;
}					t_point3d;

typedef struct s_point2d
{
	double			x;
	double			y;
}					t_point2d;

static t_point2d	iso_transform_2d(t_point3d in_p)
{
	t_point2d	out;
	double		angle;
	double		cos_a;
	double		sin_a;

	angle = M_PI / 4.0;
	cos_a = cos(angle);
	sin_a = sin(angle);
	out.x = (in_p.x - in_p.y) * cos_a;
	out.y = (in_p.x + in_p.y) * sin_a - in_p.z;
	return (out);
}

static void	set_corners(t_calc *c)
{
	c->corners[0][0] = 0.0;
	c->corners[0][1] = 0.0;
	c->corners[0][2] = c->min_z;
	c->corners[1][0] = 0.0;
	c->corners[1][1] = 0.0;
	c->corners[1][2] = c->max_z;
	c->corners[2][0] = c->w - 1.0;
	c->corners[2][1] = 0.0;
	c->corners[2][2] = c->min_z;
	c->corners[3][0] = c->w - 1.0;
	c->corners[3][1] = 0.0;
	c->corners[3][2] = c->max_z;
	c->corners[4][0] = 0.0;
	c->corners[4][1] = c->h - 1.0;
	c->corners[4][2] = c->min_z;
	c->corners[5][0] = 0.0;
	c->corners[5][1] = c->h - 1.0;
	c->corners[5][2] = c->max_z;
	c->corners[6][0] = c->w - 1.0;
	c->corners[6][1] = c->h - 1.0;
	c->corners[6][2] = c->min_z;
	c->corners[7][0] = c->w - 1.0;
	c->corners[7][1] = c->h - 1.0;
	c->corners[7][2] = c->max_z;
}

static void	calc_bounds(t_calc *c)
{
	int			i;
	t_point3d	in_p;
	t_point2d	out;

	c->min_x = DBL_MAX;
	c->max_x = -DBL_MAX;
	c->min_y = DBL_MAX;
	c->max_y = -DBL_MAX;
	i = 0;
	while (i < 8)
	{
		in_p.x = c->corners[i][0];
		in_p.y = c->corners[i][1];
		in_p.z = c->corners[i][2];
		out = iso_transform_2d(in_p);
		if (out.x < c->min_x)
			c->min_x = out.x;
		if (out.x > c->max_x)
			c->max_x = out.x;
		if (out.y < c->min_y)
			c->min_y = out.y;
		if (out.y > c->max_y)
			c->max_y = out.y;
		i++;
	}
}

static void	calc_scale_shift(t_fdf *fdf, t_calc *c)
{
	c->box_w = c->max_x - c->min_x;
	c->box_h = c->max_y - c->min_y;
	c->scale_x = (double)fdf->window.width / c->box_w;
	c->scale_y = (double)fdf->window.height / c->box_h;
	if (c->scale_x < c->scale_y)
		c->scale = c->scale_x * 0.8;
	else
		c->scale = c->scale_y * 0.8;
	fdf->scale = c->scale;
	fdf->shift_x = fdf->window.width / 2 - (int)(c->scale * (c->min_x
				+ c->max_x) / 2.0);
	fdf->shift_y = fdf->window.height / 2 - (int)(c->scale * (c->min_y
				+ c->max_y) / 2.0);
}

void	adjust_view(t_fdf *fdf)
{
	t_calc	c;

	c.w = (double)fdf->map.width;
	c.h = (double)fdf->map.height;
	c.min_z = (double)fdf->map.min_z;
	c.max_z = (double)fdf->map.max_z;
	set_corners(&c);
	calc_bounds(&c);
	calc_scale_shift(fdf, &c);
}
