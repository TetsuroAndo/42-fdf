# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 08:18:22 by teando            #+#    #+#              #
#    Updated: 2024/11/20 05:14:56 by teando           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= fdf
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
ROOT_DIR	:= .
OUT_DIR		:= $(ROOT_DIR)/objs
INCS_DIR	:= $(ROOT_DIR)/incs
LIBFT_H		:= libft.h
IDFLAGS		:= -I$(INCS_DIR)

SRCS 		:= \
	$(addprefix $(ROOT_DIR)/, \
		$(addprefix srcs/, \
		) \
	)
OBJS		:= $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))

ifeq ($(DEBUG), 1)
CFLAGS		+= -g
else
CFLAGS		+= -O2
endif

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $@ $^

$(OUT_DIR)/%.o: %.c $(LIBFT_H)
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -MMD -MP $(IDFLAGS) $< -o $@

clean:
	rm -rf $(OUT_DIR)

fclean: clean
	rm -f $(NAME) $(NAME_SO) a.out

re: fclean all

sub:
	git submodule update --init --recursive

sub-update:
	git submodule update --remote

norm: $(LIBFT_H) $(INCS_DIR) $(SRCS)
	@norminette $^

test: test.c
	$(CC) -g -fsanitize=address $< -o $@ -I. -Wl,-rpath . -L. -lft -lm

push:
	git add . && git status
	git commit -m "makepush"
	git push

.PHONY: all clean fclean re bonus norm test