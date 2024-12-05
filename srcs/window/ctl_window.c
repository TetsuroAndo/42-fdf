/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctl_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 00:53:38 by teando            #+#    #+#             */
/*   Updated: 2024/12/05 11:55:22 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief ウィンドウにピクセルを描画する
 *
 * この関数は、指定された（x, y）座標位置に指定された色のピクセルを
 * ウィンドウのイメージバッファに配置します。関数は描画を試みる前に、
 * 座標がウィンドウの境界内にあるかどうかをチェックします。
 *
 * @param fdf ウィンドウ情報を含むfdf構造体へのポインタ
 * @param x 描画するピクセルのx座標
 * @param y 描画するピクセルのy座標
 * @param color 16進数形式でのピクセルの色
 */
void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < fdf->window.width && y >= 0 && y < fdf->window.height)
	{
		dst = fdf->window.data_addr + (y * fdf->window.width + x
				* (fdf->window.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	close_window(t_fdf *fdf)
{
	free_fdf(fdf);
	exit(0);
}
