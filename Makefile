# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 15:59:55 by katakada          #+#    #+#              #
#    Updated: 2025/06/15 12:48:43 by kharuya          ###   ########.fr        #
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

BUILTINS		=	builtins/
EXEC			=	exec/
LEXING			=	lexing/
PARSING			=	parsing/
EXPANDING		=	expanding/
SIGNAL			=	signal/
UTILS			=	utils/
SRCS			=	$(BUILTINS)builtins_utils.c $(BUILTINS)cd.c $(BUILTINS)cd_utils.c $(BUILTINS)echo.c \
					$(BUILTINS)env.c $(BUILTINS)exit.c $(BUILTINS)export_utils.c \
					$(BUILTINS)export.c $(BUILTINS)pwd.c $(BUILTINS)unset.c \
					$(EXEC)ctrl_stds.c $(EXEC)err_msg_builtin_1.c $(EXEC)err_msg_builtin_2.c \
					$(EXEC)err_msg_external.c $(EXEC)err_msg_redirection.c $(EXEC)exec_abs.c \
					$(EXEC)exec_cmd_builtin.c $(EXEC)exec_cmd_external.c \
					$(EXEC)exec_cmd_redirection.c $(EXEC)exec_cmd.c $(EXEC)exec_pipe.c \
					$(EXEC)exec_subshell.c $(EXEC)exec_utils.c  $(EXEC)exec.c  $(EXEC)get_path.c \
					$(EXPANDING)ambiguous_redirection.c $(EXPANDING)expand__env_var__expand_plain_word.c \
					$(EXPANDING)expand__env_var__expand_quoted_word.c $(EXPANDING)expand__env_var__split__utils.c \
					$(EXPANDING)expand__env_var__split_post_expanded__utils.c $(EXPANDING)expand__env_var__split_post_expanded.c \
					$(EXPANDING)expand__env_var__utils.c $(EXPANDING)expand__env_var.c \
					$(EXPANDING)expand__wildcard__can_replace_wildcard.c \
					$(EXPANDING)expand__wildcard__extract_tokens_for_wildcard_check.c \
					$(EXPANDING)expand__wildcard__utils.c \
					$(EXPANDING)expand__wildcard.c $(EXPANDING)expand_abs_node__expanding_tokens_to_arg_list.c \
					$(EXPANDING)expand_abs_node.c $(EXPANDING)expander__utils.c $(EXPANDING)expander.c \
					$(LEXING)/lexer.c $(LEXING)lexicize_func_sign.c $(LEXING)lexicize_text.c $(LEXING)lexing__utils.c \
					$(PARSING)check_grammar.c $(PARSING)grammar__next_token.c $(PARSING)grammar__prefix.c $(PARSING)grammar__utils.c \
					$(PARSING)grammar_binop_pipe.c $(PARSING)grammar_quote.c $(PARSING)grammar_redirect.c \
					$(PARSING)grammar_subshell_to_redirect.c $(PARSING)grammar_subshell.c $(PARSING)grammar_text.c \
					$(PARSING)heredoc__utils.c $(PARSING)heredoc.c $(PARSING)parser__utils.c $(PARSING)parser.c \
					$(PARSING)put_syntax_err.c $(PARSING)treeing__tokens_to_abs_tree__add_command__utils.c \
					$(PARSING)treeing__tokens_to_abs_tree__add_command.c $(PARSING)treeing__tokens_to_abs_tree__insert_node.c \
					$(PARSING)treeing__tokens_to_abs_tree__utils.c $(PARSING)treeing__tokens_to_abs_tree.c \
					$(PARSING)treeing__utils.c \
					$(SIGNAL)signal.c $(SIGNAL)signal__utils.c \
					$(UTILS)clean_and_exit.c $(UTILS)dictionary.c $(UTILS)free_tools.c $(UTILS)util_tools.c \
					dialog_minishell.c init_env.c init_env__shlvl.c init_env__utils.c main.c
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

bonus:	$(NAME)

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

.PHONY:	all bonus clean fclean re debug va