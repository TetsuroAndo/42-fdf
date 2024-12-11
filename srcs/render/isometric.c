/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:22:45 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 11:18:47 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief `fdf->projected` に確保されたメモリを解放する関数。
 *
 * @param fdf メイン構造体へのポインタ
 *
 * @details `project_points()` で確保された `fdf->projected` は
 * `fdf->map.height` 行分のメモリを持つ。全ての行をfreeし、最後に
 * `fdf->projected` 自体もfreeすることでメモリリークを防ぐ。
 */
void	free_projected(t_fdf *fdf)
{
	size_t	y;

	y = 0;
	while (y < fdf->map.height)
		free(fdf->projected[y++]);
	free(fdf->projected);
}

/**
 * @brief 座標をアイソメトリック投影で変換する補助関数。
 *
 * @param fdf メイン構造体へのポインタ
 * @param x   X座標への参照(変換後の値を直接代入するためポインタ)
 * @param y   Y座標への参照(同上)
 * @param z   Z座標(高さ情報)
 *
 * @details 与えられた(x, y, z)をアイソメトリックな視点から見た投影座標へ変換する。
 * 回転角度は45度(π/4)で固定し、scaleやshiftも反映させる。
 * 結果的に2D平面上に立体的なマップを投影するための座標が得られる。
 */
static void	isometric(t_fdf *fdf, int *x, int *y, int z)
{
	double	angle;
	double	cos_a;
	double	sin_a;
	double	dx;
	double	dy;

	dx = (double)*x;
	dy = (double)*y;
	angle = M_PI / 4.0;
	cos_a = cos(angle);
	sin_a = sin(angle);
	dx = (dx - dy) * cos_a;
	dy = ((double)*x + (double)*y) * sin_a - (double)z * fdf->z_scale;
	dx = dx * fdf->scale + fdf->shift_x;
	dy = dy * fdf->scale + fdf->shift_y;
	*x = (int)dx;
	*y = (int)dy;
}

/**
 * @brief `fdf->projected` 用の2次元配列を確保する補助関数。
 *
 * @param fdf メイン構造体へのポインタ
 *
 * @details `fdf->map.height` 行、`fdf->map.width` 列分の `t_point`配列を確保し、
 * `fdf->projected` に格納する。
 * メモリ確保に失敗した場合、`ft_error()` を呼びエラー終了する。
 */
static void	allocate_projected(t_fdf *fdf)
{
	size_t	y;

	fdf->projected = (t_point **)malloc(sizeof(t_point *) * fdf->map.height);
	if (!fdf->projected)
		ft_error("Failed to allocate memory for projected points", fdf);
	y = 0;
	while (y < fdf->map.height)
	{
		fdf->projected[y] = (t_point *)malloc(sizeof(t_point) * fdf->map.width);
		if (!fdf->projected[y])
			ft_error("Failed to allocate memory for projected row", fdf);
		y++;
	}
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
		free_projected(fdf);
	allocate_projected(fdf);
	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			fdf->projected[y][x].x = x;
			fdf->projected[y][x].y = y;
			fdf->projected[y][x].z = fdf->map.points[y][x].z;
			isometric(fdf, &fdf->projected[y][x].x, &fdf->projected[y][x].y,
				fdf->projected[y][x].z);
			x++;
		}
		y++;
	}
}
