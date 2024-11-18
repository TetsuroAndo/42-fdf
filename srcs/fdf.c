/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:12:55 by teando            #+#    #+#             */
/*   Updated: 2024/11/18 06:24:24 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	*data;

	if (argc != 2)
	{
		ft_dprintf(STDERR_FILENO, "Usage: %s <mapfile.fdf>\n", argv[0]);
		return (1);
	}
	data = init_fdf();
	if (!data)
		return (1);
	if (!read_map(data, argv[1]))
	{
		free_fdf(data);
		return (1);
	}
	setup_mlx(data);
	draw(data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_key_hook(data->win, key_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
