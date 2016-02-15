#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlize <vlize@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/31 09:31:19 by vlize             #+#    #+#              #
#    Updated: 2015/03/31 09:31:20 by vlize            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = rtv1

SRC_NAME =	rtv1.c rtv1_exit.c rtv1_init.c rtv1_read.c rtv1_set.c rtv1_draw.c \
			rtv1_equation.c rtv1_calc_obj.c rtv1_calc_sub.c rtv1_normal.c \
			rtv1_calc_lux.c rtv1_calc_spot.c rtv1_make_obj.c rtv1_calc_obj2.c \
			rtv1_normal2.c

LIB =	-L ./libft/ -lft \
		-lmlx -lm \
		-framework OpenGL -framework AppKit

INC =	-I ./include/ \
		-I /usr/local/include/ \
		-I /System/Library/Frameworks/Tk.framework/Headers/

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC_PATH = ./src/

OBJ_PATH = ./obj/

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

CMP = gcc -Wall -Wextra -Werror

.PHONY: all clean fclean re

all : $(NAME)

$(NAME) :
		@ make -C libft/
		@ $(CMP) $(INC) -c $(SRC)
		@ mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
		@ mv $(OBJ_NAME) $(OBJ_PATH)
		@ $(CMP) -o $(NAME) $(OBJ) $(LIB)
		@ echo "\x1b[32m>make all : \tOK\x1b[0m"

clean :
		@ make -C libft/ clean
		@ rm -rf $(OBJ)
		@ rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
		@ echo "\x1b[32m>make clean :\tOK\x1b[0m"

fclean : clean
		@ make -s -C libft/ fclean
		@ rm -rf $(NAME)
		@ echo "\x1b[32m>make fclean :\tOK\x1b[0m"

re : fclean all
		@ echo "\x1b[32m>make re :  \tOK\x1b[0m"
