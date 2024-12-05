/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:13:12 by teando            #+#    #+#             */
/*   Updated: 2024/12/05 12:39:25 by teando           ###   ########.fr       */
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
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define ESC 65307
# define CLOSE_WINDOW 17

# define PI 3.14159265358979323846
# define ISOMETRIC_ANGLE (PI / 4)

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
	size_t		width;
	size_t		height;
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
	void		*img_ptr;
	char		*data_addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
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

typedef struct s_line
{
	int			dx;
	int			dy;
	int			xi;
	int			yi;
	int			D;
	int			x;
	int			y;
}				t_line;

/*** srcs ***/
void			ft_error(char *msg);
void			free_fdf(t_fdf *fdf);

/*** set data ***/
int				open_file(char *file_name);
t_map			read_map(char *file_name);
t_point			**allocate_points(size_t width, size_t height);
void			parse_map_size(int fd, size_t *width, size_t *height);
void			parse_line(char *line, t_point *points, size_t width, size_t y);

// color.c
int				get_default_color(int z, int min_z, int max_z);
int				parse_color(const char *str);
int				interpolate_color(int color1, int color2, double percentage);

/*** render ***/
void			draw_map(t_fdf *fdf);
void			isometric(t_fdf *fdf, int *x, int *y, int z);
void			draw_line_low(t_fdf *fdf, t_point start, t_point end);
void			draw_line_high(t_fdf *fdf, t_point start, t_point end);

/*** window ***/
void			put_pixel(t_fdf *fdf, int x, int y, int color);
int				init_window(t_fdf *fdf);
int				close_window(t_fdf *fdf);

/*** events ***/
int				key_press(int keycode, t_fdf *fdf);

#endif