/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:17:34 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 18:51:32 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	open_file(char *file_name, t_fdf *fdf)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_error(strerror(errno), fdf);
	return (fd);
}
