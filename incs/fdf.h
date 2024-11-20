/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:13:12 by teando            #+#    #+#             */
/*   Updated: 2024/11/20 08:58:47 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/libft/libft.h"
# include "../libs/minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# define PRM matrix[0][0]

typedef struct
{
	float	x;
	float	y;
	float	z;
	int		is_last;
	int		color;
	void	*mlx_ptr;
	void	*win_ptr;
}			t_dot;

t_dot		**read_map(char *file_name);
void		draw(t_dot **matrix);
int			deal_key(int key, t_dot **matrix);
void		ft_error(char *msg);

#endif