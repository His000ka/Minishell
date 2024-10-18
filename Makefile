# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 11:56:28 by pitroin           #+#    #+#              #
#    Updated: 2024/10/10 12:32:33 by pitroin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -ggdb3 -g
LIBFT_DIR = libft
PRINTF_DIR = printf
INCLUDES = -I $(LIBFT_DIR) -I src
LIBFT = $(LIBFT_DIR)/libft.a

# Readline inclusion and library paths
READLINE_DIR = /usr/local
INCLUDES += -I $(READLINE_DIR)/include
LIBS = -L $(READLINE_DIR)/lib -lreadline

# Object directory
OBJ_DIR = obj

# Source and object files
SRCS = $(shell find src -name '*.c')
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME) -L ~/.homebrew/opt/readline/lib -I ~/.homebrew/opt/readline/include -lreadline

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
