/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:21:56 by teando            #+#    #+#             */
/*   Updated: 2024/12/03 23:30:07 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_fdf	*init_fdf(void)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)ft_calloc(1, sizeof(t_fdf));
	if (!fdf)
		ft_error("Failed to allocate memory for fdf");
	return (fdf);
}

static void	free_fdf(t_fdf *fdf)
{
	size_t	i;

	if (fdf)
	{
		if (fdf->map.points)
		{
			i = 0;
			while (i < fdf->map.height)
			{
				free(fdf->map.points[i]);
				i++;
			}
			free(fdf->map.points);
		}
		free(fdf);
	}
}

void	print_map_data(t_map map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			ft_printf("(%d,%d,%d,0x%X) ", map.points[y][x].x,
				map.points[y][x].y, map.points[y][x].z, map.points[y][x].color);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

int	main(int ac, char **av)
{
	t_fdf	*fdf;

	if (ac != 2)
		return (ft_dprintf(2, "Usage: %s <map_file.fdf>\n", av[0]));
	fdf = init_fdf();
	if (!fdf)
		return (1);
	fdf->map = read_map(av[1]);
	if (fdf->map.points == NULL)
	{
		free_fdf(fdf);
		return (1);
	}
	ft_printf("Map loaded successfully. Dimensions: %dx%d\n", fdf->map.width,
		fdf->map.height);
	ft_printf("Z range: min=%d, max=%d\n", fdf->map.min_z, fdf->map.max_z);
	ft_printf("\nMap data:\n");
	print_map_data(fdf->map);
	free_fdf(fdf);
	return (0);
}
