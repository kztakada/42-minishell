# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: katakada <katakada@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 15:59:55 by katakada          #+#    #+#              #
#    Updated: 2025/04/01 16:53:05 by katakada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CC				=	cc
DEBUG_CC		=	cc -D IS_DEBUG=1 -g -fsanitize=address

CFLAGS			=	-Wall -Wextra -Werror

INCS			=	-I includes/

SRC_PATH		=	src/
SRCS			=	$(wildcard $(SRC_PATH)*.c)

OBJS_PATH		=	objs/
OBJS			=	$(SRCS:src/%.c=objs/%.o)

ISDEBUG = 0

ifeq ($(ISDEBUG), 1)
	CC = $(DEBUG_CC)
endif



$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCS) $(OBJS) -o $(NAME)

$(OBJS_PATH)%.o : $(SRC_PATH)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@


all:	$(NAME)

debug: 
	$(MAKE) ISDEBUG=1 all


clean:
	rm -rf $(OBJS_PATH)

fclean:
	rm -rf $(OBJS_PATH)
	rm -f $(NAME)

re:		fclean all

.PHONY:	all clean fclean re debug