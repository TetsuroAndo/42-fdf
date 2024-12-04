/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 06:19:57 by teando            #+#    #+#             */
/*   Updated: 2024/12/05 06:20:06 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_fdf(t_fdf *fdf)
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
