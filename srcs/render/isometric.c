/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:22:45 by teando            #+#    #+#             */
/*   Updated: 2024/12/05 12:39:35 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(t_fdf *fdf, int *x, int *y, int z)
{
	double	previous_x;

	previous_x = *x;
	*x = (int)((previous_x - *y) * cos(fdf->camera.angle));
	*y = (int)((previous_x + *y) * sin(fdf->camera.angle) - z * fdf->z_scale);
	*x = *x * fdf->scale + fdf->shift_x;
	*y = *y * fdf->scale + fdf->shift_y;
}
