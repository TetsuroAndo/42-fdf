/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:31:05 by teando            #+#    #+#             */
/*   Updated: 2024/11/18 11:32:34 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
#define GET_NEXT_LINE_BONUS_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 4096
#endif

#ifndef FD_MAX
#define FD_MAX 1024
#endif

#include "../libs/libft/libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

char *get_next_line(int fd);

#endif