/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:13:04 by teando            #+#    #+#             */
/*   Updated: 2024/12/04 04:02:05 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief 2次元配列のメモリを解放する
 *
 * この関数は2次元配列（char **）のメモリを指定されたインデックスまで解放します。
 * 解放中にエラーが発生した場合、ft_errorを呼び出します。
 *
 * @param ptr 解放する2次元配列
 * @param i 配列を解放するインデックス
 * @param is_error 解放後にft_errorを呼び出すかどうかを示すフラグ
 */
static void	ft_free_list(char **ptr, size_t i, int is_error)
{
	if (!ptr)
		return ;
	if (i == 0)
		while (ptr[i])
			free(ptr[i++]);
	else
		while (i > 0)
			free(ptr[--i]);
	free(ptr);
	if (is_error)
		ft_error("Error: Memory allocation failed");
}

/**
 * @brief 入力ファイルからマップの寸法を決定する
 *
 * この関数はファイルを1行ずつ読み込み、マップの高さと
 * 全行にわたる最小幅（ポイント数）を決定します。
 *
 * @param fd 開いたマップファイルのファイルディスクリプタ
 * @param width 決定された幅を格納するポインタ
 * @param height 決定された高さを格納するポインタ
 */
void	parse_map_size(int fd, size_t *width, size_t *height)
{
	char	*line;
	size_t	line_width;
	size_t	min_width;
	size_t	line_count;

	line_count = 0;
	min_width = SIZE_MAX;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_width = ft_count_words(line, ' ');
		if (line_width < min_width)
			min_width = line_width;
		free(line);
		line_count++;
		line = get_next_line(fd);
	}
	*width = min_width;
	*height = line_count;
	if (*width == 0 || *height == 0)
		ft_error("Error: Invalid map size");
}

/**
 * @brief ポイントの2次元配列のメモリを確保する
 *
 * この関数はマップの幅と高さに基づいてt_point構造体の
 * 2次元配列のメモリを確保します。
 *
 * @param width マップの幅
 * @param height マップの高さ
 * @return t_point** 確保されたt_point構造体の2次元配列
 */
t_point	**allocate_points(size_t width, size_t height)
{
	t_point	**points;
	size_t	i;

	points = (t_point **)malloc(sizeof(t_point *) * height);
	if (!points)
		ft_error("Error: Memory allocation failed");
	i = 0;
	while (i < height)
	{
		points[i] = (t_point *)malloc(sizeof(t_point) * width);
		if (!points[i])
			ft_free_list((char **)points, i, 1);
		i++;
	}
	return (points);
}

/**
 * @brief マップファイルの1行を解析する
 *
 * この関数はマップファイルの1行を取り、それをt_point構造体の
 * 配列に変換します。z値と色の両方を処理します。
 *
 * @param line マップファイルからの入力行
 * @param points 解析されたポイントを格納する配列
 * @param width マップの幅（1行あたりのポイント数）
 * @param y マップ内のy座標（行番号）
 */
void	parse_line(char *line, t_point *points, size_t width, size_t y)
{
	char	**values;
	size_t	x;
	char	*z_str;

	values = ft_split(line, ' ');
	if (!values)
		ft_error("Error: Split failed");
	x = -1;
	while (++x < width && values[x])
	{
		points[x].x = x;
		points[x].y = y;
		if (ft_strchr(values[x], ','))
			z_str = ft_strndup(values[x], ft_strchr(values[x], ',')
					- values[x]);
		else
			z_str = ft_strdup(values[x]);
		if (!z_str)
			ft_free_list(values, x, 1);
		points[x].z = ft_atoi(z_str);
		free(z_str);
		points[x].color = parse_color(values[x]);
	}
	ft_free_list(values, 0, 0);
}
