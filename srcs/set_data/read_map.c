/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:48:08 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 12:47:15 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief 読み込んだ行(y番目)のデータを用いて、マップ中のZ値の最小値・最大値を更新します。
 *
 * @param fdf fdf構造体へのポインタ（map.points, map.min_z, map.max_zを参照）
 * @param y 更新対象の行インデックス
 *
 * @return なし
 *
 * @details
 * 各行の全てのx列についてZ値を確認し、map.min_zより小さければ更新、map.max_zより大きければ更新します。
 */
static void	update_map_z_range(t_fdf *fdf, size_t y)
{
	size_t	x;

	x = 0;
	while (x < fdf->map.width)
	{
		if (fdf->map.points[y][x].z < fdf->map.min_z)
			fdf->map.min_z = fdf->map.points[y][x].z;
		if (fdf->map.points[y][x].z > fdf->map.max_z)
			fdf->map.max_z = fdf->map.points[y][x].z;
		x++;
	}
}

/**
 * @brief ファイルから行単位でデータを読み込み、parse_lineでpoints配列へ格納、その後Z範囲を更新します。
 *
 * @param fd 既にopenされているマップファイルのディスクリプタ
 * @param fdf fdf構造体へのポインタ（map.pointsを初期化済みであること）
 *
 * @return なし
 *
 * @details
 * map.height行分だけ読み込みを行い、1行ずつparse_lineを実行します。
 * 各行処理後にupdate_map_z_rangeでZ範囲を更新します。
 */
static void	parse_map_lines(int fd, t_fdf *fdf)
{
	char	*line;
	size_t	y;

	y = 0;
	line = get_next_line(fd);
	while (y < fdf->map.height && line != NULL)
	{
		parse_line(line, y, fdf);
		update_map_z_range(fdf, y);
		free(line);
		y++;
		line = get_next_line(fd);
	}
}

/**
 * @brief マップを読み込む前準備を行い、map構造体を初期化します。
 *
 * @param file_name 読み込むマップファイル名
 * @param fdf fdf構造体へのポインタ（結果が格納される）
 *
 * @return 初期化済みの t_map 構造体
 *
 * @details
 * ファイルを開いてマップサイズを取得し、ファイルを閉じた後でpointsを確保します。
 * Zの初期範囲をINT_MAX/INT_MINで初期化します。
 */
static t_map	init_map(char *file_name, t_fdf *fdf)
{
	t_map	map;
	int		fd;

	fd = open_file(file_name, fdf);
	parse_map_size(fd, fdf);
	close(fd);
	map.points = allocate_points(fdf);
	map.min_z = INT_MAX;
	map.max_z = INT_MIN;
	return (map);
}

/**
 * @brief 指定されたファイルからマップデータを読み込み、fdf->mapに格納して返します。
 *
 * @param file_name 読み込むマップファイル名
 * @param fdf fdf構造体へのポインタ
 *
 * @return 読み込み後の t_map 構造体
 *
 * @details
 * init_mapでマップを初期化し、再度ファイルを開いて行ごとの読み込み（parse_map_lines）を行います。
 * 最終的にfdf->mapに完全なマップ情報が格納されます。
 */
t_map	read_map(char *file_name, t_fdf *fdf)
{
	t_map	map;
	int		fd;

	map = init_map(file_name, fdf);
	fdf->map = map;
	fd = open_file(file_name, fdf);
	parse_map_lines(fd, fdf);
	close(fd);
	return (fdf->map);
}
