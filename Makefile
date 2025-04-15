# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: katakada <katakada@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 15:59:55 by katakada          #+#    #+#              #
#    Updated: 2025/04/15 17:31:42 by katakada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CC				=	cc
DEBUG_CC		=	cc -D IS_DEBUG=1 -g -fsanitize=address

CFLAGS			=	-Wall -Wextra -Werror

INCS			=	-I includes/ -I $(LIBFT_DIR)

LIBFT_DIR		=	libraries/
LIBFT			=	$(LIBFT_DIR)libft.a

SRC_PATH		=	
SRCS			=	$(wildcard $(SRC_PATH)*.c)

OBJS_PATH		=	objs/
OBJS			=	$(SRCS:%.c=objs/%.o)

ISDEBUG = 0

ifeq ($(ISDEBUG), 1)
	CC = $(DEBUG_CC)
endif



$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

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