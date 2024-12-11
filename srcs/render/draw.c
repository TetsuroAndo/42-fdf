/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:42:24 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 18:28:31 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_line_data
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
}			t_line_data;

/**
 * @brief 直線描画用の補助データを初期化する関数。
 *
 * @param data 直線描画用データを格納する構造体へのポインタ
 * @param start 線分の始点座標
 * @param end   線分の終点座標
 *
 * @details Bresenhamを応用した描画用に、x方向・y方向の増分、誤差値等を計算し構造体に格納する。
 */
static void	init_line_data(t_line_data *data, t_point start, t_point end)
{
	data->dx = ft_abs(end.x - start.x);
	data->dy = -ft_abs(end.y - start.y);
	if (start.x < end.x)
		data->sx = 1;
	else
		data->sx = -1;
	if (start.y < end.y)
		data->sy = 1;
	else
		data->sy = -1;
	data->err = data->dx + data->dy;
}

/**
 * @brief 二点間を直線で繋ぐ描画処理を行う関数。
 *
 * @param fdf   メイン構造体へのポインタ(描画情報を保持)
 * @param start 線分の始点座標
 * @param end   線分の終点座標
 *
 * @details Bresenham法を用いて二点間を繋ぐ直線を描画する。
 * `init_line_data()`で初期化された情報を用いて線上の全ての点を`put_pixel()`で描画する。
 * 勾配に応じてxまたはyをインクリメントしながら最短経路でピクセルを結ぶ。
 */
static void	draw_line(t_fdf *fdf, t_point start, t_point end)
{
	t_line_data	data;
	int			e2;

	init_line_data(&data, start, end);
	while (1)
	{
		put_pixel(fdf, start.x, start.y, start.color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * data.err;
		if (e2 >= data.dy)
		{
			data.err += data.dy;
			start.x += data.sx;
		}
		if (e2 <= data.dx)
		{
			data.err += data.dx;
			start.y += data.sy;
		}
	}
}

/**
 * @brief マップ上の全ての線分を描画する関数。
 *
 * @param fdf メイン構造体へのポインタ
 *
 * @details `fdf->projected` 内の座標情報を用いて、隣接する点同士を直線で結びワイヤーフレームを描画する。
 * 行方向、列方向それぞれに対して隣り合う点を`draw_line()`で結び、完成後にイメージをウィンドウへ出力する。
 */
void	draw_map(t_fdf *fdf)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (x < fdf->map.width - 1)
				draw_line(fdf, fdf->projected[y][x], fdf->projected[y][x + 1]);
			if (y < fdf->map.height - 1)
				draw_line(fdf, fdf->projected[y][x], fdf->projected[y + 1][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->window.mlx_ptr, fdf->window.win_ptr,
		fdf->window.img_ptr, 0, 0);
}
