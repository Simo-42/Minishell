# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhajji-b <mhajji-b@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/08 15:43:01 by fililafrapp       #+#    #+#              #
#    Updated: 2023/08/29 15:05:15 by mhajji-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = $(addprefix Src/, main.c lexer/lexer_utils.c lexer/lex.c lexer/lexer.c parser/parser.c parser/parser2.c parser/rm_para_quote.c \
					parser/parser_utils.c init_env/init_env.c signals/signals.c init_exec/init_exec.c init_exec/init_exec_utils.c \
					init_exec/init_export.c init_exec/init_fd.c exec/close_fd.c signals/signals2.c\
					built_in/pwd.c built_in/echo.c built_in/echo_utils.c built_in/cd.c built_in/built_in_utils.c built_in/env.c\
					built_in/env_create.c built_in/export_parsing.c built_in/export_var_exist.c built_in/export.c built_in/export_checking.c\
					init_exec/here_doc.c exec/child.c exec/exec_utils.c exec/prep_exec.c exec/redir_child.c \
					expander/expand2.c built_in/ft_exit.c free_all/free1.c expander/expand_utils.c built_in/built_in_utils_2.c \
					built_in/export_create.c built_in/export_parsing_2.c built_in/env_things.c expander/malloc_expand.c \
					expander/quoteandnode.c expander/expand.c expander/expand_len.c expander/splitandquote.c expander/state_quote.c parser/parser4.c \
					built_in/echo2.c init_env/init_env2.c built_in/cd2.c built_in/cd3.c built_in/write_echo.c)	
OBJ = $(SRCS:.c=.o)

CC = cc
RM = rm -f
CFLAGS = -g -g3 -Wall -Wextra -Werror

NAME = Minishell

all : $(NAME)

$(NAME) : $(OBJ)
	cd Lib && make
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) Lib/lib42.a -I ./Lib/ -lreadline

bonus : $(OBJ_BONUS)
	cd Lib && make
	$(CC) $(CFLAGS) -o $(NAME2) $(OBJ_BONUS) Lib/lib42.a -I ./Lib/ 

leak:
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=rl_leaks.txt ./$(NAME)

clean :
	cd Lib && make clean
	$(RM) $(OBJ)
	$(RM) $(OBJ_BONUS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re