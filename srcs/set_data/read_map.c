/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:42:31 by teando            #+#    #+#             */
/*   Updated: 2024/12/03 23:33:58 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief マップ内の最小および最大z値を見つける
 *
 * この関数はマップ内のすべてのポイントを反復処理し、z値の範囲を
 * 決定します。これは色のマッピングとスケーリングに有用です。
 *
 * @param map マップ構造体へのポインタ
 */
static void	find_z_range(t_map *map)
{
	size_t	x;
	size_t	y;

	map->min_z = INT_MAX;
	map->max_z = INT_MIN;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->points[y][x].z < map->min_z)
				map->min_z = map->points[y][x].z;
			if (map->points[y][x].z > map->max_z)
				map->max_z = map->points[y][x].z;
		}
	}
}

/**
 * @brief 色が指定されていないポイントにデフォルトの色を適用する
 *
 * この関数はマップ内のすべてのポイントを反復処理し、ファイルで
 * 色が指定されていない場合、z値に基づいてデフォルトの色を割り当てます。
 *
 * @param map マップ構造体へのポインタ
 */
static void	apply_default_colors(t_map *map)
{
	size_t	x;
	size_t	y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->points[y][x].color == -1)
				map->points[y][x].color = get_default_color(map->points[y][x].z,
						map->min_z, map->max_z);
		}
	}
}

/**
 * @brief マップファイルを読み込み、t_map構造体を構築する
 *
 * この関数は以下の手順を実行します：
 * 1. ファイルを開いてマップの寸法を決定
 * 2. ポイント配列のメモリを確保
 * 3. ファイルを再度読み込み、各行をポイントデータとして解析
 * 4. マップ内のz値の範囲を決定
 * 5. 色が指定されていないポイントにデフォルトの色を適用
 *
 * @param file_name マップデータを含むファイルの名前
 * @return t_map 完全に構築されたマップ構造体
 */
t_map	read_map(char *file_name)
{
	t_map	map;
	int		fd;
	char	*line;
	size_t	y;

	fd = open_file(file_name);
	parse_map_size(fd, &map.width, &map.height);
	close(fd);
	map.points = allocate_points(map.width, map.height);
	fd = open_file(file_name);
	line = get_next_line(fd);
	y = 0;
	while (y < map.height && line != NULL)
	{
		parse_line(line, map.points[y], map.width, y);
		free(line);
		y++;
		line = get_next_line(fd);
	}
	close(fd);
	find_z_range(&map);
	apply_default_colors(&map);
	return (map);
}
