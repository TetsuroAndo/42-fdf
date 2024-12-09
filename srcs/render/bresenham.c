/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 05:01:11 by teando            #+#    #+#             */
/*   Updated: 2024/12/10 06:26:21 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_line
{
	int	dx;
	int	dy;
	int	xi;
	int	yi;
	int	d;
	int	x;
	int	y;
}		t_line;

void	draw_line_low(t_fdf *fdf, t_point start, t_point end)
{
	t_line	l;
	int		x;

	l.dx = end.x - start.x;
	l.dy = end.y - start.y;
	l.yi = 1;
	if (l.dy < 0)
	{
		l.yi = -1;
		l.dy = -l.dy;
	}
	l.d = (2 * l.dy) - l.dx;
	l.y = start.y;
	x = start.x - 1;
	while (++x <= end.x)
	{
		put_pixel(fdf, x, l.y, DEFAULT_COLOR);
		if (l.d > 0)
		{
			l.y = l.y + l.yi;
			l.d = l.d + (2 * (l.dy - l.dx));
		}
		else
			l.d = l.d + 2 * l.dy;
	}
}

void	draw_line_high(t_fdf *fdf, t_point start, t_point end)
{
	t_line	l;
	int		y;

	l.dx = end.x - start.x;
	l.dy = end.y - start.y;
	l.xi = 1;
	if (l.dx < 0)
	{
		l.xi = -1;
		l.dx = -l.dx;
	}
	l.d = (2 * l.dx) - l.dy;
	l.x = start.x;
	y = start.y - 1;
	while (++y <= end.y)
	{
		put_pixel(fdf, l.x, y, DEFAULT_COLOR);
		if (l.d > 0)
		{
			l.x = l.x + l.xi;
			l.d = l.d + (2 * (l.dx - l.dy));
		}
		else
			l.d = l.d + 2 * l.dx;
	}
}
