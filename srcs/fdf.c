/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:12:55 by teando            #+#    #+#             */
/*   Updated: 2024/11/20 07:36:16 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_default(t_dot *param)
{
	param->mlx_ptr = mlx_init();
	param->win_ptr = mlx_new_window(param->mlx_ptr, 2000, 1000, "FDF");
}

int	main(int ac, char **av)
{
	t_dot	**matrix;

	if (ac != 2)
		return ((ft_dprintf(2, "Usage: %s <map_file.fdf>\n", av[0])));
	matrix = read_map(*++av);
	set_default(&PRM);
	draw(matrix);
	mlx_key_hook(PRM.win_ptr, deal_key, matrix);
	mlx_loop(PRM.mlx_ptr);
	return (0);
}
