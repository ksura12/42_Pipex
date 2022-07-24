# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 09:24:12 by ksura             #+#    #+#              #
#    Updated: 2022/07/24 11:03:14 by ksura            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex
CC = gcc
CFLAGS := -Wall -Werror -Wextra
LIBRARIES = $(FT_LNK) 
HEADER = ./header
SRCDIR = src/
OBJDIR := build/

LIBFT = $(LIBFT_DIRECTORY)/libft.a
LIBFT_DIRECTORY = ./libft
FT_LNK	= ./libft/libft.a

SRC := main.c test.c

GREEN = \033[0;32m
RED = \033[0;31m

OBJS = ${SRC:.c=.o}
OBJECTS_PREF := $(addprefix $(OBJDIR), $(OBJS))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS_PREF) $(OBJDIR)
	@$(CC) $(FLAGS) $(OBJECTS_PREF) $(LIBRARIES) -I$(HEADER) -o $@
	@echo "$(GREEN)$(NAME) was created"
	
$(LIBFT):
	@cd ./$(LIBFT_DIRECTORY) && make all

$(OBJECTS_PREF): build/%.o : src/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(OBLI) -c $< -o $@ -I$(HEADER) $(INCLUDES)

clean:
	@cd ./$(LIBFT_DIRECTORY) && make clean
	@rm -rf $(OBJDIR)

fclean: clean
	@cd ./$(LIBFT_DIRECTORY) && make fclean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) was deleted"

re: fclean all

debug: $(LIBFT) $(OBJECTS_PREF) $(OBJDIR)
	$(CC) $(FLAGS) $(OBJECTS_PREF) $(LIBRARIES) -I$(HEADER) -o $(NAME) -g