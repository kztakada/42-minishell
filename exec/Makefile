# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 15:59:55 by katakada          #+#    #+#              #
#    Updated: 2025/05/18 18:23:12 by kharuya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	exec

CC				=	cc
DEBUG_CC		=	cc -D IS_DEBUG=1 -g -fsanitize=address

CFLAGS			=	-Wall -Wextra -Werror

INCS			=	-I ../includes/h_minishell.h -I ../includes/minishell.h -I $(LIBFT_DIR)

EXEC_PATH		=	
BUILTINS_PATH	=	../builtins/
SRCS			=	$(wildcard $(EXEC_PATH)*.c) $(wildcard $(BUILTINS_PATH)*.c) ../utils/dictionary.c

LIBFT_DIR		=	../libraries/
LIBFT			=	$(LIBFT_DIR)libft.a

OBJS_PATH		=	objs/
OBJS			=	$(SRCS:%.c=objs/%.o)

ISDEBUG = 0

ifeq ($(ISDEBUG), 1)
	CC = $(DEBUG_CC)
endif



$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJS_PATH)%.o : $(SRC_PATH)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

all:	$(NAME)

debug: 
	$(MAKE) ISDEBUG=1 all


clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJS_PATH)

fclean:
	make fclean -C $(LIBFT_DIR)
	rm -rf $(OBJS_PATH)
	rm -f $(NAME)

re:		fclean all

.PHONY:	all clean fclean re debug