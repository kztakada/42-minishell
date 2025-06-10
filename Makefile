# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: katakada <katakada@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 15:59:55 by katakada          #+#    #+#              #
#    Updated: 2025/06/08 02:16:00 by katakada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CC				=	cc
DEBUG_CC		=	cc -D IS_DEBUG=1 -g -fsanitize=address,undefined

CFLAGS			=	-Wall -Wextra -Werror

INCS			=	-I includes/ -I $(LIBFT_DIR) 

LIBFT_DIR		=	libraries/
LIBFT			=	$(LIBFT_DIR)libft.a

RLDIR_BREW		=	$(shell brew --prefix readline)
LIBRL			=	-lreadline

SRC_PATH		=	
SRCS			=	$(wildcard *.c) $(wildcard utils/*.c) $(wildcard lexing/*.c) $(wildcard parsing/*.c) $(wildcard expanding/*.c) $(wildcard exec/*.c) $(wildcard builtins/*.c) $(wildcard signal/*.c)

OBJS_PATH		=	objs/
OBJS			=	$(SRCS:%.c=objs/%.o)

ISDEBUG = 0

ifeq ($(ISDEBUG), 1)
	CC = $(DEBUG_CC)
endif

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	INCS += -I $(RLDIR_BREW)/include
    LIBRL = -L $(RLDIR_BREW)/lib -lreadline
endif

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCS) $(OBJS) $(LIBFT) $(LIBRL) -o $(NAME) 

$(OBJS_PATH)%.o : $(SRC_PATH)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	make bonus -C $(LIBFT_DIR)


all:	$(NAME)

debug:
	make fclean
	$(MAKE) ISDEBUG=1 all

va:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=.suppression ./$(NAME)


clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJS_PATH)

fclean:
	make fclean -C $(LIBFT_DIR)
	rm -rf $(OBJS_PATH)
	rm -f $(NAME)

re:		fclean all

.PHONY:	all clean fclean re debug va