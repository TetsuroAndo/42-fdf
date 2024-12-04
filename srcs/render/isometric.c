/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:22:45 by teando            #+#    #+#             */
/*   Updated: 2024/12/05 06:58:45 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric_projection(t_fdf *fdf, int *x, int *y, int z)
{
	int	previous_x;
	int	previous_y;

	if (fdf->camera.is_isometric)
	{
		previous_x = *x;
		previous_y = *y;
		*x = (previous_x - previous_y) * cos(fdf->camera.angle);
		*y = -z * fdf->z_scale + (previous_x + previous_y)
			* sin(fdf->camera.angle);
		ft_printf("Isometric projection: (%d, %d, %d) -> (%d, %d)\n",
			previous_x, previous_y, z, *x, *y);
	}
	*x = *x * fdf->scale + fdf->shift_x;
	*y = *y * fdf->scale + fdf->shift_y;
}
