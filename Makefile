# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 08:18:22 by teando            #+#    #+#              #
#    Updated: 2024/11/22 12:13:38 by teando           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= fdf
CC			:= cc
FRAMEWORKS	:= -lmlx -lXext -lX11 -lm
CFLAGS		:= #-Wall -Wextra -Werror
ROOT_DIR	:= .
OUT_DIR		:= $(ROOT_DIR)/objs
INCS_DIR	:= $(ROOT_DIR)/incs
LIBFT_DIR	:= $(ROOT_DIR)/libs/libft
LIBFT		:= $(LIBFT_DIR)/libft.a
MLX_DIR		:= $(ROOT_DIR)/libs/minilibx
MLX			:= $(MLX_DIR)/libmlx.a

IDFLAGS		:= -I$(INCS_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

SRCS 		:= \
	$(addprefix srcs/, \
		deal_key.c \
		draw.c \
		error_handler.c \
		fdf.c \
		open_map.c \
		read_map.c \
		ch_wd.c \
	)

OBJS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS		:= $(OBJS:.o=.d)

ifeq ($(DEBUG), 1)
	CFLAGS	+= -g -fsanitize=address
else
	CFLAGS	+= -O2
endif

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L$(MLX_DIR) $(FRAMEWORKS) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(OUT_DIR)/%.o: $(ROOT_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP $(IDFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OUT_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

reb:
	rm -rf $(OUT_DIR) $(NAME)
	$(MAKE) all
	
sub:
	git submodule update --init --recursive

subup:
	git submodule update --remote

norm:
	@norminette $(SRCS) $(INCS_DIR)

debug:
	$(MAKE) DEBUG=1

.PHONY: all clean fclean re sub sub-update norm debug

-include $(DEPS)