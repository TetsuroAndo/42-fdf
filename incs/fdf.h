/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:13:12 by teando            #+#    #+#             */
/*   Updated: 2024/11/18 23:54:57 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/libft/libft.h"
# include <math.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct
{
	float		x;
	float		y;
	float		z;
	int			is_last;
	int			color;
	int			scale;
	int			z_scale;
	int			shift_x;
	int			shift_y;
	int			is_isometric;
	double		angle;
	int			win_x;
	int			win_y;
	void		*mlx_ptr;
	void		*win_ptr;
}				t_dot;

// t_fdf	*init_fdf(void);
// int		read_map(t_fdf *data, char *filename);
// void	setup_mlx(t_fdf *data);
// void	draw(t_fdf *data);
// int		close_window(t_fdf *data);
// int		key_hook(int keycode, t_fdf *data);
// void	free_fdf(t_fdf *data);

char	*get_next_