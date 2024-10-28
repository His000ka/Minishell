# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 11:56:28 by pitroin           #+#    #+#              #
#    Updated: 2024/10/28 09:48:13 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -ggdb3
LIBFT_DIR = libft
PRINTF_DIR = printf
INCLUDES = -I $(LIBFT_DIR) -I src
LIBFT = $(LIBFT_DIR)/libft.a

READLINE_DIR = /usr/local
INCLUDES += -I $(READLINE_DIR)/include
LIBS = -L $(READLINE_DIR)/lib -lreadline

OBJ_DIR = obj

SRCS = \
	src/main.c \
	src/built-in/cd.c \
	src/built-in/echo.c \
	src/built-in/env.c \
	src/built-in/env_2.c \
	src/built-in/exit.c \
	src/built-in/export.c \
	src/built-in/export_2.c \
	src/built-in/ft_builtin.c \
	src/built-in/pwd.c \
	src/built-in/unset.c \
	src/built-in/utils/ft_utils.c \
	src/control/control.c \
	src/exec/error_msg.c \
	src/exec/exec.c \
	src/exec/execve.c \
	src/exec/pipe.c \
	src/exec/pipe_2.c \
	src/exec/utils.c \
	src/exec/exec_append/exec_append.c \
	src/exec/exec_input/exec_input.c \
	src/exec/exec_trunc/exec_trunc.c \
	src/exec/heredoc/heredoc.c \
	src/exec/heredoc/heredoc_2.c \
	src/init/env.list.c \
	src/init/init_shelly.c \
	src/lexer/count_elem.c \
	src/lexer/count_elem2.c \
	src/lexer/expender.c \
	src/lexer/info_elem.c \
	src/lexer/lexer.c \
	src/lexer/split_cmd.c \
	src/lexer/token_str.c \
	src/lexer/utils_lexer.c \
	src/parser/ast.c \
	src/parser/ast_2.c \
	src/parser/check_mult.c \
	src/parser/parser.c \
	src/utils/free.c \
	src/utils/utils.c \
	src/utils/affiche.c

OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re