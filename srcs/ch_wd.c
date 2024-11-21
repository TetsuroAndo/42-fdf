/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_wd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:42:15 by teando            #+#    #+#             */
/*   Updated: 2024/11/21 15:42:46 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_win_size(int key, t_dot **matrix)
{
	if ((key == 0 && PRM.win_y <= 500) || (key == 6 && PRM.win_x <= 500))
		return (1);
	if ((key == 1 && PRM.win_y > 1000) || (key == 7 && PRM.win_x > 2000))
		return (1);
	return (0);
}

void	full_screen(t_dot **matrix)
{
	static int	old_x;
	static int	old_y;

	if (PRM.win_x != 2560)
	{
		old_x = PRM.win_x;
		old_y = PRM.win_y;
	}
	PRM.win_x = (PRM.win_x == 2560) ? old_x : 2560;
	PRM.win_y = (PRM.win_y == 1400) ? old_y : 1400;
}

void	change_window_size(int key, t_dot **matrix)
{
	if (check_win_size(key, matrix))
		return ;
	if (key == 6)
		PRM.win_x -= 100;
	if (key == 7)
		PRM.win_x += 100;
	if (key == 0)
		PRM.win_y -= 100;
	if (key == 1)
		PRM.win_y += 100;
	if (key == 3)
		full_screen(matrix);
}

void	new_window(int key, t_dot **matrix)
{
	change_window_size(key, matrix);
	mlx_destroy_window(PRM.mlx_ptr, PRM.win_ptr);
	PRM.mlx_ptr = mlx_init();
	PRM.win_ptr = mlx_new_window(PRM.mlx_ptr, PRM.win_x, PRM.win_y, "FDF");
	PRM.shift_x = PRM.win_x / 3;
	PRM.shift_y = PRM.win_y / 3;
	draw(matrix);
	mlx_key_hook(PRM.win_ptr, deal_key, matrix);
	mlx_loop(PRM.mlx_ptr);
}

void	print_menu(t_dot param)
{
	char	*menu;

	menu = "up, down, left, right: move picture";
	mlx_string_put(param.mlx_ptr, param.win_ptr, 10, 5, 0x03fc35, menu);
	menu = "5, spase: 3d/2d mode; +, -: zoom";
	mlx_string_put(param.mlx_ptr, param.win_ptr, 10, 20, 0x03fc35, menu);
	menu = "8, 2: z-scale; 4, 6: rotation";
	mlx_string_put(param.mlx_ptr, param.win_ptr, 10, 35, 0x03fc35, menu);
	menu = "f: full screen mode";
	mlx_string_put(param.mlx_ptr, param.win_ptr, 10, 50, 0x03fc35, menu);
}
