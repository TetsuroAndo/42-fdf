/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 06:19:57 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 10:26:13 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_fdf(t_fdf *fdf)
{
	size_t	i;

	if (fdf)
	{
		if (fdf->projected)
			free_projected(fdf);
		if (fdf->map.points)
		{
			i = 0;
			while (i < fdf->map.height)
				free(fdf->map.points[i++]);
			free(fdf->map.points);
		}
		if (fdf->window.img_ptr)
			mlx_destroy_image(fdf->window.mlx_ptr, fdf->window.img_ptr);
		if (fdf->window.win_ptr)
			mlx_destroy_window(fdf->window.mlx_ptr, fdf->window.win_ptr);
		if (fdf->window.mlx_ptr)
		{
			mlx_destroy_display(fdf->window.mlx_ptr);
			mlx_loop_end(fdf->window.mlx_ptr);
			free(fdf->window.mlx_ptr);
		}
		free(fdf);
	}
}
