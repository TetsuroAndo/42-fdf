/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 06:16:58 by teando            #+#    #+#             */
/*   Updated: 2024/12/12 13:27:54 by teando           ###   ########.fr       */
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
# define DEFAULT_COLOR 0xFFFFFF
# define X 0
# define Y 1
# define Z 2

typedef enum e_projection
{
	ISO = 0,
	PARALLEL
}					t_projection;

typedef struct s_point2d
{
	double			x;
	double			y;
}					t_point2d;

typedef struct s_point3d
{
	double			x;
	double			y;
	double			z;
}					t_point3d;

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_point;

typedef struct s_map
{
	t_point			**points;
	size_t			width;
	size_t			height;
	int				min_z;
	int				max_z;
}					t_map;

typedef struct s_window
{
	int				width;
	int				height;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_window;

typedef struct s_fdf
{
	t_point			**projected;
	t_map			map;
	t_window		window;
	double			scale;
	double			z_scale;
	int				shift_x;
	int				shift_y;
	t_projection	projection_mode;
	double			rot_x;
	double			rot_y;
	double			rot_z;
}					t_fdf;

/*** events ***/
int					key_press(int keycode, t_fdf *fdf);

/*** render ***/
void				draw_map(t_fdf *fdf);
void				project_points(t_fdf *fdf);
t_point2d			iso_transform_2d(t_point3d in_p);

/*** set data ***/
int					open_file(char *file_name, t_fdf *fdf);
t_map				read_map(char *file_name, t_fdf *fdf);
t_point				**allocate_points(t_fdf *fdf, size_t height, size_t width);
void				parse_map_size(int fd, t_fdf *fdf);
void				parse_line(char *line, size_t y, t_fdf *fdf);
void				adjust_view(t_fdf *fdf);

/*** window ***/
void				put_pixel(t_fdf *fdf, int x, int y, int color);
int					init_window(t_fdf *fdf);
int					close_window(t_fdf *fdf);

/*** srcs ***/
void				ft_error(char *msg, t_fdf *fdf);
void				free_2d_char(char **arr);
void				free_2d_points(t_point **arr, size_t len);
void				free_fdf(t_fdf *fdf);

#endif