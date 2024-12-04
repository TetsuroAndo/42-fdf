/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctl_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 00:53:38 by teando            #+#    #+#             */
/*   Updated: 2024/12/05 06:42:52 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < fdf->window.width && y >= 0 && y < fdf->window.height)
	{
		dst = fdf->window.data_addr + (y * fdf->window.width + x
				* (fdf->window.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	close_window(t_fdf *fdf)
{
	if (fdf->window.img_ptr)
		mlx_destroy_image(fdf->window.mlx_ptr, fdf->window.img_ptr);
	if (fdf->window.win_ptr)
		mlx_destroy_window(fdf->window.mlx_ptr, fdf->window.win_ptr);
	if (fdf->window.mlx_ptr)
	{
		mlx_destroy_display(fdf->window.mlx_ptr);
		free(fdf->window.mlx_ptr);
	}
	free_fdf(fdf);
	exit(0);
}
