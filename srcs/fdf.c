/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:21:56 by teando            #+#    #+#             */
/*   Updated: 2024/12/05 13:36:41 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_fdf	*init_fdf(void)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)ft_calloc(1, sizeof(t_fdf));
	if (!fdf)
		ft_error("Failed to allocate memory for fdf");
	fdf->scale = 30;
	fdf->z_scale = 1;
	fdf->camera.angle = ISOMETRIC_ANGLE;
	// fdf->shift_x = 200;
	// fdf->shift_y = 100;
	fdf->camera.is_isometric = 1;
	fdf->window.width = 1200;
	fdf->window.height = 800;
	return (fdf);
}

static void	print_map_data(t_map map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			ft_printf("(%d,%d,%d,0x%X) ", map.points[y][x].x,
				map.points[y][x].y, map.points[y][x].z, map.points[y][x].color);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

int	main(int ac, char **av)
{
	t_fdf	*fdf;

	if (ac != 2)
		return ((ft_dprintf(2, "Usage: %s <map_file.fdf>\n", av[0])));
	fdf = init_fdf();
	fdf->map = read_map(av[1]);
	if (fdf->map.points == NULL)
	{
		free_fdf(fdf);
		return (1);
	}
	if (!init_window(fdf))
	{
		free_fdf(fdf);
		return (1);
	}
	// print_map_data(fdf->map);
	draw_map(fdf);
	mlx_hook(fdf->window.win_ptr, CLOSE_WINDOW, 0, close_window, fdf);
	mlx_key_hook(fdf->window.win_ptr, key_press, fdf);
	mlx_loop(fdf->window.mlx_ptr);
	free_fdf(fdf);
	return (0);
}
