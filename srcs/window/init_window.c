/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:23:23 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 15:32:15 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "fdf.h"

/**
 * @brief ウィンドウとイメージの初期化を行う関数
 *
 * @param fdf メインのデータ構造体へのポインタ
 * @return int 初期化成功時は1、失敗時は0を返す
 *
 * この関数は以下の4つの主要な初期化ステップを実行します：
 * 1. MLXライブラリの初期化 (mlx_init)
 * 2. 新規ウィンドウの作成 (mlx_new_window)
 * 3. 新規イメージの作成 (mlx_new_image)
 * 4. イメージデータアドレスの取得 (mlx_get_data_addr)
 *
 * 各ステップで失敗した場合は即座に0を返してエラーを通知します。
 */
int init_window(t_fdf *fdf)
{
	fdf->window.mlx_ptr = mlx_init();
	if (!fdf->window.mlx_ptr)
		return (0);
	fdf->window.win_ptr = mlx_new_window(fdf->window.mlx_ptr, fdf->window.width,
										 fdf->window.height, "FDF");
	if (!fdf->window.win_ptr)
		return (0);
	fdf->window.img_ptr = mlx_new_image(fdf->window.mlx_ptr, fdf->window.width,
										fdf->window.height);
	if (!fdf->window.img_ptr)
		return (0);
	fdf->window.data_addr = mlx_get_data_addr(fdf->window.img_ptr,
											  &fdf->window.bits_per_pixel, &fdf->window.size_line,
											  &fdf->window.endian);
	return (1);
}
