/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:22:45 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 18:36:00 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief 座標をアイソメトリック投影で変換する補助関数。
 *
 * @param fdf メイン構造体へのポインタ
 * @param x   X座標への参照(変換後の値を直接代入するためポインタ)
 * @param y   Y座標への参照(同上)
 * @param z   Z座標(高さ情報)
 *
 * @details 与えられた(x, y, z)をアイソメトリックな視点から見た投影座標へ変換する。
 * 回転角度は30度(π/6)で固定し、scaleやshiftも反映させる。
 * 結果的に2D平面上に立体的なマップを投影するための座標が得られる。
 */
static void	isometric(t_fdf *fdf, int *x, int *y, int z)
{
	double	angle;
	double	cos_a;
	double	sin_a;
	double	x_iso;
	double	y_iso;

	angle = M_PI / 6.0;
	cos_a = cos(angle);
	sin_a = sin(angle);
	x_iso = ((double)*x - (double)*y) * cos_a;
	y_iso = ((double)*x + (double)*y) * sin_a - (double)z * fdf->z_scale;
	*x = (int)(x_iso * fdf->scale + fdf->shift_x);
	*y = (int)(y_iso * fdf->scale + fdf->shift_y);
}

/**
 * @brief マップ上の各座標点をアイソメトリック投影した2D座標へ変換する関数。
 *
 * @param fdf メイン構造体へのポインタ
 *
 * @details `fdf->map.points` に格納された3D座標を `projected` に投影する。
 * 既に`projected`が確保済みの場合は解放後に再確保し、
 * 各点を`isometric()`で投影変換する。
 */
void	project_points(t_fdf *fdf)
{
	size_t	y;
	size_t	x;

	if (fdf->projected)
		free_2d_points(fdf->projected, fdf->map.height);
	fdf->projected = allocate_points(fdf, fdf->map.height, fdf->map.width);
	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			fdf->projected[y][x].x = (int)x;
			fdf->projected[y][x].y = (int)y;
			fdf->projected[y][x].z = fdf->map.points[y][x].z;
			fdf->projected[y][x].color = fdf->map.points[y][x].color;
			isometric(fdf, &fdf->projected[y][x].x, &fdf->projected[y][x].y,
				fdf->projected[y][x].z);
			x++;
		}
		y++;
	}
}
