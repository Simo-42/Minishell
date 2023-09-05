# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/08 16:29:32 by fililafrapp       #+#    #+#              #
#    Updated: 2023/08/29 12:56:07 by fililafrapp      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lib42.a
FT_PRINTF = $(addprefix Src/ft_, len_nb_hexa.c len_nb.c memset.c pointeur.c printf.c putchar.c \
putnbr_base_hex.c putnbr_base_neg.c putnbr_base.c putstr.c strjoin2.c strncmp.c putstr_fd.c strchr.c atoll.c)
GNL = $(addprefix Src/, get_next_line.c get_next_line_utils.c)
OBJS_FT = ${FT_PRINTF:.c=.o}
OBJS_GNL = ${GNL:.c=.o}
OBJ = $(OBJS_FT) $(OBJS_GNL)
CC = gcc
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re