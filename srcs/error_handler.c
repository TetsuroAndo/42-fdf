/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:13:08 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 10:34:32 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(char *msg, t_fdf *fdf)
{
	ft_dprintf(STDERR_FILENO, "%s\n", msg);
	if (fdf)
		free_fdf(fdf);
	exit(EXIT_FAILURE);
}
