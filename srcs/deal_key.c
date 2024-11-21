/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 07:36:32 by teando            #+#    #+#             */
/*   Updated: 2024/11/21 11:40:01 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	deal_key(int key, t_dot **matrix)
{
	if (key == 53)
	{
		mlx_destroy_window(PRM.mlx_ptr, PRM.win_ptr);
		free(matrix);
		exit(0);
	}
	return (0);
}
