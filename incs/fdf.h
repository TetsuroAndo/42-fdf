/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:13:12 by teando            #+#    #+#             */
/*   Updated: 2024/11/21 12:06:56 by teando           ###   ########.fr       */
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

# define PRM matrix[0][0]

typedef struct
{
	float	x;
	float	y;
	float	z;
	int		is_last;

	int		is_isometric;
	double	angle;
	int		win_x;
	int		win_y;
	void	*mlx_ptr;
	void	*win_ptr;
}			t_dot;

t_dot		**read_map(char *file_name);
void		draw(t_dot **matrix);
int			deal_key(int key, t_dot **matrix);
void		ft_error(char *msg);
int			open_file(char *file_name);
void		set_param(t_dot *a, t_dot *b, t_dot *param);
void		isometric(t_dot *dot, double angle);

#endif