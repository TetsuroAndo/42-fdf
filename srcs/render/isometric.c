/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:22:45 by teando            #+#    #+#             */
/*   Updated: 2024/12/10 05:43:10 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(t_fdf *fdf, int *x, int *y, int z)
{
	double	previous_x;
	double	angle;

	angle = PI / 4;
	previous_x = *x;
	*x = (int)((previous_x - *y) * cos(angle) * fdf->scale);
	*y = (int)(((previous_x + *y) * sin(angle) - z * fdf->z_scale)
			* fdf->scale);
	*x += fdf->shift_x;
	*y += fdf->shift_y;
}
