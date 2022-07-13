# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxenceeudier <maxenceeudier@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/27 09:36:17 by meudier           #+#    #+#              #
#    Updated: 2022/07/13 17:02:26 by ammah            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -Wall -Wextra -Werror -g

NAME = minishell

SRC = utils/ft_isalnum.c utils/ft_strjoin.c utils/ft_split.c src/main.c \
	utils/ft_strdup.c utils/ft_strlen.c utils/ft_strcmp.c \
	lexer/ft_split_lexer.c execute/pipe.c parser/parser.c lexer/lexer.c \
	src/close.c utils/ft_calloc.c utils/cpy.c execute/execute.c \
	execute/get_cmdpath.c execute/dup.c lexer/ft_split_lexer_2.c \
	src/write_error.c parser/parser_action.c parser/parser2.c \
	builtin/env.c src/sig.c builtin/builtin.c builtin/gestion_variables.c \
	lexer/ft_expand.c lexer/ft_expand_2.c parser/parser_action_2.c \
	builtin/cd.c builtin/pwd.c builtin/export.c builtin/unset.c \
	builtin/env_2.c builtin/echo.c utils/ft_isdigit.c utils/ft_ltoi.c \
	builtin/exit.c
	
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
