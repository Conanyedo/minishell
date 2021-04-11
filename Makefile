# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 22:34:18 by ybouddou          #+#    #+#              #
#    Updated: 2021/04/03 14:40:10 by cabouelw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell.a
LIB_PATH = Libft
LIB = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c\
	tools.c\
	tools_plus.c\
	expansions.c\
	commands.c\
	linkedlist.c\
	builtins/ft_env.c\
	builtins/ft_echo.c\
	builtins/ft_exit.c\
	builtins/ft_cd.c\
	builtins/ft_unset.c\
	builtins/ft_pwd.c\
	builtins/ft_export.c\
	builtins/export.c\
	builtins/utils.c\
	builtins.c\
	tokens/ft_redirecting.c\
	tokens/ft_open_fd.c\
	pars_src/check_point.c\
	pars_src/check_quotation.c\
	pars_src/parsing.c\
	errors/errors_parsing.c\
	errors/errors_cmd.c\
	pars_src/check_symbols.c\
	pars_src/check_pipes.c\
	errors/errors_cmd.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	@ar rcs $(NAME) $(OBJ)
	@gcc $(NAME) $(LIB_PATH)/$(LIB) -o minishell

$(LIB):
	@make -C $(LIB_PATH)

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@make clean -C $(LIB_PATH)/
	@rm -rf $(OBJ)

fclean: clean
#	@make fclean -C
	@rm -rf $(NAME)

re: fclean all
