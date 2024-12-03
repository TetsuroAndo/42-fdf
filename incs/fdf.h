/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:13:12 by teando            #+#    #+#             */
/*   Updated: 2024/12/03 23:44:59 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/libft/libft.h"
# include "../libs/minilibx/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define PRM matrix[0][0]

typedef struct s_point
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_point;

typedef struct s_map
{
	t_point		**points;
	int			width;
	int			height;
	int			min_z;
	int			max_z;
}				t_map;

typedef struct s_camera
{
	double		angle;
	int			is_isometric;
}				t_camera;

typedef struct s_window
{
	int			width;
	int			height;
	void		*mlx_ptr;
	void		*win_ptr;
}				t_window;

typedef struct s_fdf
{
	t_map		map;
	t_camera	camera;
	t_window	window;
	int			scale;
	int			z_scale;
	int			shift_x;
	int			shift_y;
}				t_fdf;

/*** srcs ***/

void			ft_error(char *msg);

/*** set data ***/
// open_map.c
int				open_file(char *file_name);
// read_map.c
t_map			read_map(char *file_name);
// parse_dot.c
t_point			**allocate_points(size_t width, size_t height);
void			parse_map_size(int fd, size_t *width, size_t *height);
void			parse_line(char *line, t_point *points, size_t width, size_t y);
// color.c
int				get_default_color(int z, int min_z, int max_z);
int				parse_color(const char *str);
// set_param.c

#endif