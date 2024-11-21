/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:14:32 by teando            #+#    #+#             */
/*   Updated: 2024/11/21 11:39:53 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_param(t_dot *a, t_dot *b, t_dot *param)
{
	if (param->is_isometric)
	{
		isometric(a, param->angle);
		isometric(b, param->angle);
	}
}
