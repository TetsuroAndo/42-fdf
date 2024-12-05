/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 05:01:11 by teando            #+#    #+#             */
/*   Updated: 2024/12/05 11:55:58 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief 線形補間のためのパラメーターtを計算する
 *
 * この関数は、startとendの間の線形補間のためのパラメーターtを計算します。
 * パラメーターtは、(current - start) / (end - start)で計算されます。
 * もしendがstartと等しい場合、この関数は0.0を返します。
 * これは、startがendと等しい場合、補間は意味を持たないためです。
 * @param current 現在の値
 * @param start 開始値
 * @param end 終了値
 * @return パラメーターt
 */
static double	calculate_t(int current, int start, int end)
{
	if (end == start)
		return (0.0);
	return ((double)(current - start) / (end - start));
}

/**
 * @brief 画面上に開始点から終点まで線を描画する（下向き）
 * @details この関数は、画面上の開始点から終点まで線を描画するための
 *          t_line構造体を初期化するために使用されます。
 *          線は下向きに描画されます（つまり、開始点から終点にかけて
 *          yの値が増加します）。
 * @param l 初期化対象のt_line構造体
 * @param start 線の開始点
 * @param end 線の終点
 */
static void	draw_line_low_init(t_line *l, t_point start, t_point end)
{
	l->dx = end.x - start.x;
	l->dy = end.y - start.y;
	l->yi = 1;
	if (l->dy < 0)
	{
		l->yi = -1;
		l->dy = -l->dy;
	}
	l->D = (2 * l->dy) - l->dx;
	l->y = start.y;
}

/**
 * @brief 画面上に開始点から終点まで線を描画する（下向き）
 * @details この関数は、画面上の開始点から終点まで線を描画します。
 *          線は下向きに描画されます（つまり、開始点から終点にかけてyの値が増加します）。
 * @param fdf 描画用のデータを含むfdf構造体
 * @param start 線の開始点
 * @param end 線の終点
 */
void	draw_line_low(t_fdf *fdf, t_point start, t_point end)
{
	t_line	l;
	int		x;
	double	t;
	int		color;

	draw_line_low_init(&l, start, end);
	x = start.x;
	while (x <= end.x)
	{
		t = calculate_t(x, start.x, end.x);
		color = interpolate_color(start.color, end.color, t);
		put_pixel(fdf, x, l.y, color);
		if (l.D > 0)
		{
			l.y = l.y + l.yi;
			l.D = l.D + (2 * (l.dy - l.dx));
		}
		else
			l.D = l.D + 2 * l.dy;
		x++;
	}
}

/**
 * @brief 画面上に開始点から終点まで線を描画するためのt_line構造体を初期化する（high）
 * @details この関数は、画面上の開始点から終点まで線を描画するための
 *          t_line構造体を初期化するために使用されます。
 *          線はhighに描画されます（つまり、開始点から終点にかけて
 *          xの値が増加します）。
 * @param l 初期化対象のt_line構造体
 * @param start 線の開始点
 * @param end 線の終点
 */
static void	draw_line_high_init(t_line *l, t_point start, t_point end)
{
	l->dx = end.x - start.x;
	l->dy = end.y - start.y;
	l->xi = 1;
	if (l->dx < 0)
	{
		l->xi = -1;
		l->dx = -l->dx;
	}
	l->D = (2 * l->dx) - l->dy;
	l->x = start.x;
}

/**
 * @brief 画面上に開始点から終点まで線を描画する（high）
 * @details この関数は、画面上の開始点から終点まで線を描画します。
 *          線はhigh方向に描画されます（つまり、開始点から終点にかけて
 *          xの値が増加します）。
 * @param fdf 描画用のデータを含むfdf構造体
 * @param start 線の開始点
 * @param end 線の終点
 */
void	draw_line_high(t_fdf *fdf, t_point start, t_point end)
{
	t_line	l;
	int		y;
	double	t;
	int		color;

	draw_line_high_init(&l, start, end);
	y = start.y;
	while (y <= end.y)
	{
		t = calculate_t(y, start.y, end.y);
		color = interpolate_color(start.color, end.color, t);
		put_pixel(fdf, l.x, y, color);
		if (l.D > 0)
		{
			l.x = l.x + l.xi;
			l.D = l.D + (2 * (l.dx - l.dy));
		}
		else
			l.D = l.D + 2 * l.dx;
		y++;
	}
}
