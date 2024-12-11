/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 05:01:11 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 11:17:22 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_line
{
	int	dx;
	int	dy;
	int	xi;
	int	yi;
	int	d;
	int	x;
	int	y;
}		t_line;

/**
 * @brief 緩やかな傾斜(勾配が1未満)の直線をBresenhamのアルゴリズムで描画する関数。
 *
 * @param fdf   メイン構造体へのポインタ。画面描画用の情報を保持。
 * @param start 線分の始点座標を保持するt_point構造体。
 * @param end   線分の終点座標を保持するt_point構造体。
 *
 * @details Bresenhamのアルゴリズムを用いて、勾配が比較的水平な線分をドットで描画する。
 * 線分上の座標を計算し、`put_pixel()` を用いて画面バッファへ描画する。
 */
void	draw_line_low(t_fdf *fdf, t_point start, t_point end)
{
	t_line	l;
	int		x;

	l.dx = end.x - start.x;
	l.dy = end.y - start.y;
	l.yi = 1;
	if (l.dy < 0)
	{
		l.yi = -1;
		l.dy = -l.dy;
	}
	l.d = (2 * l.dy) - l.dx;
	l.y = start.y;
	x = start.x - 1;
	while (++x <= end.x)
	{
		put_pixel(fdf, x, l.y, DEFAULT_COLOR);
		if (l.d > 0)
		{
			l.y = l.y + l.yi;
			l.d = l.d + (2 * (l.dy - l.dx));
		}
		else
			l.d = l.d + 2 * l.dy;
	}
}

/**
 * @brief 勾配が急(1以上)の直線をBresenhamのアルゴリズムで描画する関数。
 *
 * @param fdf   メイン構造体へのポインタ。画面描画用の情報を保持。
 * @param start 線分の始点座標を保持するt_point構造体。
 * @param end   線分の終点座標を保持するt_point構造体。
 *
 * @details Bresenhamのアルゴリズムを用いて、勾配が比較的垂直に近い線分をドットで描画する。
 * 線分上の座標を計算し、`put_pixel()` を用いて画面バッファへ描画する。
 */
void	draw_line_high(t_fdf *fdf, t_point start, t_point end)
{
	t_line	l;
	int		y;

	l.dx = end.x - start.x;
	l.dy = end.y - start.y;
	l.xi = 1;
	if (l.dx < 0)
	{
		l.xi = -1;
		l.dx = -l.dx;
	}
	l.d = (2 * l.dx) - l.dy;
	l.x = start.x;
	y = start.y - 1;
	while (++y <= end.y)
	{
		put_pixel(fdf, l.x, y, DEFAULT_COLOR);
		if (l.d > 0)
		{
			l.x = l.x + l.xi;
			l.d = l.d + (2 * (l.dx - l.dy));
		}
		else
			l.d = l.d + 2 * l.dx;
	}
}
