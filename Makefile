# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 22:34:18 by ybouddou          #+#    #+#              #
#    Updated: 2021/04/18 13:37:14 by ybouddou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIB_PATH = Libft
LIB = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NCURSES= -lncurses
SRC = main.c\
	tools.c\
	expansions.c\
	commands.c\
	utils.c\
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
	readline/history.c\
	readline/keys.c\
	readline/readline.c\
	readline/utils.c\
	readline/signals.c\
	readline/term.c\
	readline/deleting.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	@gcc $(OBJ) $(LIB_PATH)/$(LIB) $(NCURSES) -o $(NAME)

$(LIB):
	@make -C $(LIB_PATH)

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@make clean -C $(LIB_PATH)/
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C $(LIB_PATH)
	@rm -rf $(NAME)

re: fclean all
