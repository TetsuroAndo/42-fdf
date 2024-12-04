/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:43:44 by teando            #+#    #+#             */
/*   Updated: 2024/12/05 05:19:22 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief 16進数の色文字列を検証する
 *
 * この関数は、与えられた文字列が有効な16進数の色であるかチェックします。
 * オプションで "0x" または "0X" のプレフィックスと、最大6桁の16進数を許可します。
 *
 * @param str 検証する文字列
 * @return int 有効な場合は1、無効な場合は0
 */
static int	validate_hex_color(const char *str)
{
	size_t	i;

	if (!str || !*str)
		return (0);
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		str += 2;
	i = 0;
	while (str[i] && ft_isxdigit(str[i]))
		i++;
	return (str[i] == '\0' && i <= 6);
}

/**
 * @brief 文字列表現から色を解析する
 *
 * この関数は文字列から色の値を抽出します。色は16進数形式で、
 * オプションでコンマでプレフィックスされていることを想定しています。
 *
 * @param str 色情報を含む文字列
 * @return int 解析された色を整数として返す。無効な場合は-1
 */
int	parse_color(const char *str)
{
	const char	*color_start;
	long		color;

	if (!str)
		return (-1);
	color_start = ft_strchr(str, ',');
	if (!color_start)
		return (-1);
	color_start++;
	if (!validate_hex_color(color_start))
		return (-1);
	color = ft_strtol(color_start, NULL, 16);
	if (color >= 0 && color <= 0xFFFFFF)
		return ((int)color);
	return (-1);
}

/**
 * @brief 2つの色の間を補間する
 *
 * この関数は、与えられた2つの色の間の中間色を、
 * パーセンテージ値に基づいて計算します。
 *
 * @param color1 開始色
 * @param color2 終了色
 * @param percentage 補間のパーセンテージ（0.0から1.0）
 * @return int 補間された色
 */
int	interpolate_color(int color1, int color2, double percentage)
{
	int	r;
	int	g;
	int	b;

	r = (color1 >> 16) & 0xFF;
	g = (color1 >> 8) & 0xFF;
	b = color1 & 0xFF;
	r += ((color2 >> 16) & 0xFF - r) * percentage;
	g += ((color2 >> 8) & 0xFF - g) * percentage;
	b += ((color2 & 0xFF - b) * percentage);
	return ((r << 16) | (g << 8) | b);
}

/**
 * @brief z値に基づいてデフォルトの色を生成する
 *
 * この関数は、ポイントのz値に基づいて色のグラデーションを作成します。
 * 青 -> 緑 -> 黄 -> 赤の4色グラデーションを使用します。
 *
 * @param z ポイントのz値
 * @param min_z マップ内の最小z値
 * @param max_z The maximum z-value in the map
 * @return int型の算出された色
 */
int	get_default_color(int z, int min_z, int max_z)
{
	const int	colors[] = {0x0000FF, 0x00FF00, 0xFFFF00, 0xFFA500, 0xFF0000};
	double		percentage;
	int			idx;

	if (min_z == max_z)
		return (0xFFFFFF);
	percentage = (double)(z - min_z) / (max_z - min_z);
	if (percentage >= 1.0)
		return (0xFF0000);
	idx = (int)(percentage * 4);
	percentage = (percentage * 4) - idx;
	return (interpolate_color(colors[idx], colors[idx + 1], percentage));
}
// int	get_default_color(int z, int min_z, int max_z)
// {
// 	double	percentage;
// 	int		color1;
// 	int		color2;

// 	if (min_z == max_z)
// 		return (0xFFFFFF);
// 	percentage = (double)(z - min_z) / (max_z - min_z);
// 	if (percentage < 0.25)
// 	{
// 		color1 = 0x0000FF;
// 		color2 = 0x00FF00;
// 		percentage = percentage * 4;
// 	}
// 	else if (percentage < 0.5)
// 	{
// 		color1 = 0x00FF00;
// 		color2 = 0xFFFF00;
// 		percentage = (percentage - 0.25) * 4;
// 	}
// 	else if (percentage < 0.75)
// 	{
// 		color1 = 0xFFFF00;
// 		color2 = 0xFFA500;
// 		percentage = (percentage - 0.5) * 4;
// 	}
// 	else
// 	{
// 		color1 = 0xFFA500;
// 		color2 = 0xFF0000;
// 		percentage = (percentage - 0.75) * 4;
// 	}
// 	return (interpolate_color(color1, color2, percentage));
// }
