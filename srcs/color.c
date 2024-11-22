/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:43:44 by teando            #+#    #+#             */
/*   Updated: 2024/11/22 16:46:07 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @param z height.
 * @param min_z minimum height.
 * @param max_z maximum height.
 * @return color value in RGB format.
 *
 * The color will be interpolated between blue (minimum height) and red
/******  b77df8f8-74d1-466d-8cde-555438a7ae9a  *******/
static int	get_color(int z, int min_z, int max_z)
{
	double	percentage;

	int r, g, b;
	if (min_z == max_z)
		return (0xFFFFFF);
	percentage = (double)(z - min_z) / (max_z - min_z);
	r = (int)(255 * percentage);
	b = (int)(255 * (1 - percentage));
	g = (int)(255 * (1 - fabs(2 * percentage - 1)));
	return ((r << 16) | (g << 8) | b);
}

int	parse_color(char *str)
{
	char	*color_start;

	color_start = ft_strchr(str, ',');
	if (color_start)
		return (ft_atoi_base(color_start + 1, 16));
	return (-1);
}
