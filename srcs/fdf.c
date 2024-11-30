/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:12:55 by teando            #+#    #+#             */
/*   Updated: 2024/11/30 21:34:15 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "fdf.h"

void init_mlx(t_fdf *fdf)
{
	fdf->window.mlx_ptr = mlx_init();
	fdf->window.win_ptr = mlx_new_window(fdf->window.mlx_ptr, 1000, 1000,
										 "FDF");
}

t_fdf *init_fdf(void)
{
	t_fdf *fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	ft_memset(fdf, 0, sizeof(t_fdf));
	fdf->scale = 30;
	fdf->z_scale = 1;
	fdf->shift_x = 0;
	fdf->shift_y = 0;
	fdf->camera.angle = 0.8;
	fdf->camera.is_isometric = 1;
	return (fdf);
}

int main(int ac, char **av)
{
	t_fdf *fdf;

	if (ac != 2)
		return ((ft_dprintf(2, "Usage: %s <map_file.fdf>\n", av[0])));
	fdf = init_fdf();
	if (!fdf)
		return (1);
	if (read_map(av[1], &fdf->map) != 0)
	{
		free_fdf(fdf);
		return (1);
	}
	init_mlx(fdf);
	draw(fdf);
	mlx_key_hook(fdf->window.win_ptr, deal_key, fdf);
	mlx_hook(fdf->window.win_ptr, 17, 0, close_window, fdf);
	mlx_loop(fdf->window.mlx_ptr);
	free_fdf(fdf);
	return (0);
}
