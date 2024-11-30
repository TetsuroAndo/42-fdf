/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:43:44 by teando            #+#    #+#             */
/*   Updated: 2024/11/25 19:16:24 by teando           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "fdf.h"

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

int	parse_color(char *str)
{
	char	*color_start;
	int		color;

	if (!str)
		return (-1);
	color_start = ft_strchr(str, ',');
	if (!color_start)
		return (-1);
	color_start++;
	if (!validate_hex_color(color_start))
		return (-1);
	color = ft_atoi_base(color_start, 16);
	return (color >= 0 ? color : -1);
}

static int	interpolate_color(int color1, int color2, double percentage)
{
	int	r;
	int	g;
	int	b;
	int	r2;
	int	g2;
	int	b2;

	r = (color1 >> 16) & 0xFF;
	g = (color1 >> 8) & 0xFF;
	b = color1 & 0xFF;
	r2 = (color2 >> 16) & 0xFF;
	g2 = (color2 >> 8) & 0xFF;
	b2 = color2 & 0xFF;
	r = r + (r2 - r) * percentage;
	g = g + (g2 - g) * percentage;
	b = b + (b2 - b) * percentage;
	return ((r << 16) | (g << 8) | b);
}

int	get_default_color(int z, int min_z, int max_z)
{
	double	percentage;
	int		color1;
	int		color2;

	if (min_z == max_z)
		return (0xFFFFFF);  // 高さの差がない場合は白
	percentage = (double)(z - min_z) / (max_z - min_z);
	
	if (percentage < 0.25)
	{
		color1 = 0x0000FF;  // 青（低地）
		color2 = 0x00FF00;  // 緑
		percentage = percentage * 4;
	}
	else if (percentage < 0.5)
	{
		color1 = 0x00FF00;  // 緑
		color2 = 0xFFFF00;  // 黄
		percentage = (percentage - 0.25) * 4;
	}
	else if (percentage < 0.75)
	{
		color1 = 0xFFFF00;  // 黄
		color2 = 0xFFA500;  // オレンジ
		percentage = (percentage - 0.5) * 4;
	}
	else
	{
		color1 = 0xFFA500;  // オレンジ
		color2 = 0xFF0000;  // 赤（高地）
		percentage = (percentage - 0.75) * 4;
	}
	
	return (interpolate_color(color1, color2, percentage));
}
