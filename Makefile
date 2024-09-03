# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pitroin <pitroin@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 11:56:28 by pitroin           #+#    #+#              #
#    Updated: 2024/09/03 14:40:36 by pitroin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
PRINTF_DIR = printf
INCLUDES = -I $(LIBFT_DIR) -I src
LIBFT = $(LIBFT_DIR)/libft.a

# Readline inclusion and library paths
READLINE_DIR = $(shell brew --prefix readline)
INCLUDES += -I $(READLINE_DIR)/include
LIBS = -L $(READLINE_DIR)/lib -lreadline -lhistory

# Source and object files
SRCS = src/main.c
OBJS = ${SRCS:.c=.o}

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
