# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 15:59:55 by katakada          #+#    #+#              #
#    Updated: 2025/04/01 19:50:25 by kharuya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CC				=	cc
DEBUG_CC		=	cc -D IS_DEBUG=1 -g -fsanitize=address

CFLAGS			=	-Wall -Wextra -Werror

INCS			=	-I includes/

SRC_PATH		=	
SRCS			=	$(wildcard $(SRC_PATH)*.c)

OBJS_PATH		=	objs/
OBJS			=	$(SRCS:%.c=objs/%.o)

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