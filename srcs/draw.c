/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:42:24 by teando            #+#    #+#             */
/*   Updated: 2024/11/21 02:31:11 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static float	fmodule(float i)
{
	if (i < 0)
		return (-i);
	return (i);
}

static void	line(t_dot a, t_dot b, t_dot *param)
{
	float	step_x;
	float	step_y;
	float	max;
	int		color;

	step_x = b.x - a.x;
	step_y = b.y - a.y;
	max = MAX(fmodule(step_x), fmodule(step_y));
	step_x /= max;
	step_y /= max;
	color = (b.z || a.z) ? 0xfc0345 : 0xBBFAFF;
	color = (b.z != a.z) ? 0xfc031c : color;
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		mlx_pixel_put(param->mlx_ptr, param->win_ptr, a.x, a.y, color);
		a.x += step_x;
		a.y += step_y;
		if (a.x > 2000 || a.y > 1000 || a.y < 0 || a.x < 0)
			break ;
	}
}

void	draw(t_dot **matrix)
{
	int	y;
	int	x;

	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (1)
		{
			if (matrix[y + 1])
				line(matrix[y][x], matrix[y + 1][x], &PRM);
			if (!matrix[y][x].is_last)
				line(matrix[y][x], matrix[y][x + 1], &PRM);
			if (matrix[y][x].is_last)
				break ;
			x++;
		}
		y++;
	}
}
