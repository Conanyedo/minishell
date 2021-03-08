# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 22:34:18 by ybouddou          #+#    #+#              #
#    Updated: 2021/03/08 11:25:15 by cabouelw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell.a
LIB_PATH = Libft
LIB = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c\
	tools.c\
	builtins/ft_env.c\
	builtins.c\
	pars_src/check_point.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@gcc $(NAME) $(LIB_PATH)/$(LIB) -o minishell

# $(LIB):
# 	@make -C $(LIB_PATH)

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@make clean -C $(LIB_PATH)/
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C
	@rm -rf $(NAME)

re: fclean all
