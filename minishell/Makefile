# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meudier <meudier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/27 09:36:17 by meudier           #+#    #+#              #
#    Updated: 2022/07/06 12:44:10 by meudier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -Wall -Wextra -Werror -g

NAME = minishell

SRC = utils/ft_strjoin.c utils/ft_split.c src/main.c \
	utils/ft_strdup.c utils/ft_strlen.c utils/ft_strcmp.c \
	src/ft_split_lexer.c src/pipe.c src/parser.c src/lexer.c \
	src/close.c utils/ft_calloc.c src/cpy.c src/execute.c \
	src/get_cmdpath.c src/dup.c src/ft_split_lexer_2.c \
	src/write_error.c src/parser_action.c src/parser2.c \
	src/env.c src/sig.c src/builtin.c
	
	
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -c $< -o $@ 

$(NAME): $(OBJ)
	$(CC) $^  -o $@ -lreadline	

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean
