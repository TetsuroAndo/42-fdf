/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:42:24 by teando            #+#    #+#             */
/*   Updated: 2024/12/05 13:35:16 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	swap_points(t_point *point1, t_point *point2)
{
	t_point	tmp;

	tmp = *point1;
	*point1 = *point2;
	*point2 = tmp;
}

/*
 * 2点間を描画するためのメイン関数
 *
 * fdf: 描画に使うfdf構造体
 * start: 描画する線分の始点
 * end: 描画する線分の終点
 *
 * 2点間を描画するために、x座標やy座標の差を計算し、どの軸に
 * 長さが大きいかを判断する。x軸に長さが大きい場合はdraw_line_lowを、
 * y軸に長さが大きい場合はdraw_line_highを呼び出す。
 */
static void	draw_line(t_fdf *fdf, t_point start, t_point end)
{
	if (ft_abs(end.y - start.y) < ft_abs(end.x - start.x))
	{
		if (start.x > end.x)
			swap_points(&start, &end);
		draw_line_low(fdf, start, end);
	}
	else
	{
		if (start.y > end.y)
			swap_points(&start, &end);
		draw_line_high(fdf, start, end);
	}
}

/*
 * 2点間を描画するための補助関数
 *
 * fdf: 描画に使うfdf構造体
 * x: 描画する点のx座標
 * y: 描画する点のy座標
 * next: 'h' or 'v'
 *          'h'の場合は水平方向に、'v'の場合は垂直方向に描画する
 *
 * fdfのmap.points[y][x]にある点と、nextの方向に隣接する点との
 * 2点間を線分で描画する
 */
static void	draw_line_point(t_fdf *fdf, int x, int y, int next)
{
	t_point	start;
	t_point	end;

	start.x = x;
	start.y = y;
	// ft_printf("Before projection: (%d, %d, %d)\n", start.x, start.y,
	// 	fdf->map.points[y][x].z);
	isometric(fdf, &start.x, &start.y, fdf->map.points[y][x].z);
	// ft_printf("After projection: (%d, %d)\n", start.x, start.y);
	start.color = fdf->map.points[y][x].color;
	// ft_printf("Start point: (%d, %d), color=%X\n", start.x, start.y,
	// 	start.color);
	if (next == 'h')
	{
		end.x = x + 1;
		end.y = y;
		isometric(fdf, &end.x, &end.y, fdf->map.points[y][x + 1].z);
		end.color = fdf->map.points[y][x + 1].color;
	}
	else
	{
		end.x = x;
		end.y = y + 1;
		isometric(fdf, &end.x, &end.y, fdf->map.points[y + 1][x].z);
		end.color = fdf->map.points[y + 1][x].color;
	}
	// ft_printf("End point: (%d, %d), color=%X\n", end.x, end.y, end.color);
	draw_line(fdf, start, end);
}

/**
 * @brief      2Dマップを描画する
 *
 *             2Dマップを描画するために、各点同士を線で結んでいく
 *             各点同士を線で結ぶために、draw_line_point関数を使う
 *
 *             2Dマップを描画するために、まず各点同士を水平方向に線で結ぶ
 *             draw_line_point関数に'h'を渡すことで、水平方向に線を描画する
 *             その後、各点同士を垂直方向に線で結ぶ
 *             draw_line_point関数に'v'を渡すことで、垂直方向に線を描画する
 *
 *             2Dマップの描画が終わった後、描画結果をウィンドウに反映する
 *             ために、mlx_put_image_to_window関数を使用する
 */
void	draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	ft_printf("Map dimensions: %d x %d\n", fdf->map.width, fdf->map.height);
	fdf->shift_x = fdf->window.width / 2 - (fdf->map.width * fdf->scale) / 2;
	fdf->shift_y = fdf->window.height / 2 - (fdf->map.height * fdf->scale) / 2;
	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			// ft_printf("Drawing point at (%d, %d), z=%d, color=%X\n", x, y,
			// 	fdf->map.points[y][x].z, fdf->map.points[y][x].color);
			if (x < fdf->map.width - 1)
				draw_line_point(fdf, x, y, 'h');
			if (y < fdf->map.height - 1)
				draw_line_point(fdf, x, y, 'v');
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->window.mlx_ptr, fdf->window.win_ptr,
		fdf->window.img_ptr, 0, 0);
}
