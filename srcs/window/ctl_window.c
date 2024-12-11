/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctl_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 00:53:38 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 18:51:49 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < fdf->window.width && y >= 0 && y < fdf->window.height)
	{
		dst = fdf->window.data_addr + (y * fdf->window.size_line + x
				* (fdf->window.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	close_window(t_fdf *fdf)
{
	free_fdf(fdf);
	exit(STDIN_FILENO);
}
