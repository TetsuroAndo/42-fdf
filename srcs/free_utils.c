/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 06:19:57 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 17:06:17 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_2d_char(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_2d_points(t_point **arr, size_t len)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	if (!len)
		while (arr[i])
			free(arr[i++]);
	else
		while (i < len)
			free(arr[i++]);
	free(arr);
}

void	free_fdf(t_fdf *fdf)
{
	if (fdf)
	{
		if (fdf->projected)
			free_2d_points(fdf->projected, 0);
		if (fdf->map.points)
			free_2d_points(fdf->map.points, fdf->map.height);
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
