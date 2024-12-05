/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:22:45 by teando            #+#    #+#             */
/*   Updated: 2024/12/05 17:07:21 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(t_fdf *fdf, int *x, int *y, int z)
{
	double	previous_x;

	previous_x = *x;
	*x = (int)((previous_x - *y) * cos(fdf->camera.angle) * fdf->scale);
	*y = (int)(((previous_x + *y) * sin(fdf->camera.angle) - z * fdf->z_scale)
			* fdf->scale);
	*x += fdf->shift_x;
	*y += fdf->shift_y;
}
