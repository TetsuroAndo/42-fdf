/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:13:04 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 12:46:30 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_free_list(char **ptr)
{
	size_t	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

/**
 * @brief マップファイルから行数と列数（最小列数）を計測し、fdf->mapに格納します。
 *
 * @param fd 既にopenされているファイルのディスクリプタ
 * @param fdf fdf構造体へのポインタ（結果のwidth, heightを格納）
 *
 * @return なし
 *
 * @details
 * ファイルを最後まで読み込み、各行の単語数（列数）をカウントします。
 * 最も小さい列数をマップの幅（width）とし、行数を高さ（height）とします。
 * widthまたはheightが0の場合はエラー終了します。
 */
void	parse_map_size(int fd, t_fdf *fdf)
{
	char	*line;
	size_t	line_width;
	size_t	min_width;
	size_t	line_count;

	min_width = SIZE_MAX;
	line_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		line_width = ft_count_words(line, ' ');
		if (line_width < min_width)
			min_width = line_width;
		free(line);
		line_count++;
		line = get_next_line(fd);
	}
	fdf->map.width = min_width;
	fdf->map.height = line_count;
	if (fdf->map.width == 0 || fdf->map.height == 0)
		ft_error("Error: Invalid map size", fdf);
}

/**
 * @brief マップ情報を格納するために、(height x width)の2次元配列(points)を確保します。
 *
 * @param fdf fdf構造体へのポインタ（map.width, map.heightを参照してメモリを確保）
 *
 * @return 確保に成功した場合、確保済みの t_point** 配列を返します。失敗時にはエラーを表示して終了します。
 *
 * @details
 * 各行ごとにメモリを確保するため、1行でも確保に失敗した場合はエラー終了します。
 */
t_point	**allocate_points(t_fdf *fdf)
{
	t_point	**points;
	size_t	i;

	points = (t_point **)malloc(sizeof(t_point *) * fdf->map.height);
	if (!points)
		ft_error("Error: Memory allocation failed", fdf);
	i = 0;
	while (i < fdf->map.height)
	{
		points[i] = (t_point *)malloc(sizeof(t_point) * fdf->map.width);
		if (!points[i])
		{
			while (i > 0)
				free(points[--i]);
			free(points);
			ft_error("Error: Memory allocation failed", fdf);
		}
		i++;
	}
	return (points);
}

/**
 * @brief 1行分の文字列を解析し、各カラムに対して(x, y, z)座標をpoints配列へ格納します。
 * 
 * @param line 1行分のマップデータ（スペース区切りのZ値）
 * @param y 現在処理している行インデックス
 * @param fdf fdf構造体へのポインタ（map.points[y]に書き込み）
 * 
 * @return なし
 * 
 * @details
 * 与えられた行をスペースで分割し、Z値を整数として読み込みます。  
 * xは列インデックス、yは行インデックスとして設定します。
 * メモリ解放やエラーチェックを適宜行います。
 */
void	parse_line(char *line, size_t y, t_fdf *fdf)
{
	char	**values;
	size_t	x;
	size_t	width;
	t_point	*points;

	width = fdf->map.width;
	points = fdf->map.points[y];
	values = ft_split(line, ' ');
	if (!values)
		ft_error("Error: Split failed", fdf);
	x = 0;
	while (x < width && values[x])
	{
		points[x].x = (int)x;
		points[x].y = (int)y;
		points[x].z = ft_atoi(values[x]);
		x++;
	}
	ft_free_list(values);
}
