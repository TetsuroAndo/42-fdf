/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 00:46:48 by teando            #+#    #+#             */
/*   Updated: 2024/12/12 13:28:40 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>

int	key_press(int keycode, t_fdf *fdf)
{
	if (keycode == ESC)
		close_window(fdf);
	// 投影切り替え (I: Iso, P: Parallel)
	if (keycode == 'i' || keycode == 'I')
		fdf->projection_mode = ISO;
	else if (keycode == 'p' || keycode == 'P')
		fdf->projection_mode = PARALLEL;
	// 回転 (W/S: X軸回り, A/D: Y軸回り, Q/E: Z軸回り)
	if (keycode == 'w' || keycode == 'W')
		fdf->rot_x += 0.05;
	else if (keycode == 's' || keycode == 'S')
		fdf->rot_x -= 0.05;
	else if (keycode == 'a' || keycode == 'A')
		fdf->rot_y += 0.05;
	else if (keycode == 'd' || keycode == 'D')
		fdf->rot_y -= 0.05;
	else if (keycode == 'q' || keycode == 'Q')
		fdf->rot_z += 0.05;
	else if (keycode == 'e' || keycode == 'E')
		fdf->rot_z -= 0.05;
	// ズーム (+/-キー)
	if (keycode == XK_plus || keycode == XK_equal)
		fdf->scale *= 1.1;
	else if (keycode == XK_minus || keycode == XK_underscore)
		fdf->scale *= 0.9;
	// 平行移動 (矢印キー)
	if (keycode == XK_Up)
		fdf->shift_y -= 10;
	else if (keycode == XK_Down)
		fdf->shift_y += 10;
	else if (keycode == XK_Left)
		fdf->shift_x -= 10;
	else if (keycode == XK_Right)
		fdf->shift_x += 10;
	// 変更があれば再描画
	project_points(fdf);
	draw_map(fdf);
	return (0);
	return (0);
}
