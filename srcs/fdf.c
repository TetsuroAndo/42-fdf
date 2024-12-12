/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:21:56 by teando            #+#    #+#             */
/*   Updated: 2024/12/12 10:56:57 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_fdf	*init_fdf(void)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)ft_calloc(1, sizeof(t_fdf));
	if (!fdf)
		ft_error("Failed to allocate memory for fdf", NULL);
	fdf->z_scale = 1;
	fdf->window.width = 3000;
	fdf->window.height = 2000;
	return (fdf);
}

int	main(int ac, char **av)
{
	t_fdf	*fdf;
	char	*extension;

	if (ac != 2)
		return (ft_dprintf(2, "Usage: %s <map_file.fdf>\n", av[0]), 1);
	extension = ft_strrchr(av[1], '.');
	if (extension == NULL || ft_strncmp(extension, ".fdf", 4) != 0)
		return (ft_dprintf(2, "Import only <.fdf> files\n", av[0]), 1);
	fdf = init_fdf();
	fdf->map = read_map(av[1], fdf);
	if (fdf->map.points == NULL)
	{
		return (free_fdf(fdf), 1);
	}
	if (!init_window(fdf))
	{
		ft_error("Failed to initialize window", fdf);
	}
	adjust_view(fdf);
	project_points(fdf);
	draw_map(fdf);
	mlx_hook(fdf->window.win_ptr, CLOSE_WINDOW, 0, close_window, fdf);
	mlx_key_hook(fdf->window.win_ptr, key_press, fdf);
	mlx_loop(fdf->window.mlx_ptr);
	return (free_fdf(fdf), 0);
}
