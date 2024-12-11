/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:23:23 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 18:51:53 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_window(t_fdf *fdf)
{
	fdf->window.mlx_ptr = mlx_init();
	if (!fdf->window.mlx_ptr)
		return (0);
	fdf->window.win_ptr = mlx_new_window(fdf->window.mlx_ptr, fdf->window.width,
			fdf->window.height, "FDF");
	if (!fdf->window.win_ptr)
		return (0);
	fdf->window.img_ptr = mlx_new_image(fdf->window.mlx_ptr, fdf->window.width,
			fdf->window.height);
	if (!fdf->window.img_ptr)
		return (0);
	fdf->window.data_addr = mlx_get_data_addr(fdf->window.img_ptr,
			&fdf->window.bits_per_pixel, &fdf->window.size_line,
			&fdf->window.endian);
	return (1);
}
