# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 22:34:18 by ybouddou          #+#    #+#              #
#    Updated: 2021/03/02 17:46:06 by ybouddou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c\
	  gnl/get_next_line.c\
	  tools.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@gcc $(NAME) Libft/libft.a -o minishell

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
