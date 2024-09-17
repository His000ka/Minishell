<<<<<<< HEAD
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: firdawssemazouz <firdawssemazouz@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 11:56:28 by pitroin           #+#    #+#              #
#    Updated: 2024/09/12 22:30:50 by firdawssema      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
LIBFT_DIR = libft
PRINTF_DIR = printf
INCLUDES = -I $(LIBFT_DIR) -I src
LIBFT = $(LIBFT_DIR)/libft.a

# Readline inclusion and library paths
READLINE_DIR = /usr/local
INCLUDES += -I $(READLINE_DIR)/include
LIBS = -L $(READLINE_DIR)/lib -lreadline

# Source and object files
SRCS = $(shell find src -name '*.c')
OBJS = $(SRCS:.c=.o)

# Rules
all: present ministar $(NAME)

# Display FIRDAWSSE AND PIERRE PRESENT MINISHELL ALIAS MINISTAR with smaller figlet fonts and colors
present:
	@echo "\033[1;33m******************************************************\033[0m"
	@figlet -f small "FIRDAWSSE AND PIERRE" | lolcat
	@figlet -f small "PRESENT MINISHELL" | lolcat
	@figlet -f small "MINISTAR" | lolcat
	@echo "\033[1;33m******************************************************\033[0m"

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "\033[0;32m[✔] Compilation complete!\033[0m"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[0;34m[✔] Compiling $<\033[0m"

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	@echo "\033[0;31m[✘] Objects cleaned!\033[0m"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "\033[0;31m[✘] Executable cleaned!\033[0m"

re: fclean all

# Animation for "ministar" with changing colors
ministar:
	@echo "\033[0;33mBuilding minishell...\033[0m"
	@for i in {1..10}; do \
		if [ $$((i % 3)) -eq 0 ]; then \
			printf "\033[0;31m🌟\033[0m"; \
		elif [ $$((i % 3)) -eq 1 ]; then \
			printf "\033[0;32m🌟\033[0m"; \
		else \
			printf "\033[0;34m🌟\033[0m"; \
		fi; \
		sleep 0.1; \
	done
	@echo "\n\033[0;36mMinishell is ready!\033[0m"

.PHONY: all clean fclean re present ministar
=======
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fimazouz <fimazouz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 11:56:28 by pitroin           #+#    #+#              #
#    Updated: 2024/09/10 13:14:09 by fimazouz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
LIBFT_DIR = libft
PRINTF_DIR = printf
INCLUDES = -I $(LIBFT_DIR) -I src
LIBFT = $(LIBFT_DIR)/libft.a

# Readline inclusion and library paths
READLINE_DIR = /usr/local
INCLUDES += -I $(READLINE_DIR)/include
LIBS = -L $(READLINE_DIR)/lib -lreadline

# Source and object files
SRCS = $(shell find src -name '*.c')
OBJS = $(SRCS:.c=.o)

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
>>>>>>> ad1b7fbba2f85588b978f7e1a88c2dd25eb29f2c
