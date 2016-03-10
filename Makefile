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

NAME = rt

SRC_NAME =	rt.c rt_exit.c rt_init.c rt_read.c rt_make.c rt_set.c rt_draw.c \
			rt_sub_function.c rt_equation.c rt_cubic.c rt_quartic.c rt_check.c \
			rt_spot.c rt_lux.c rt_object.c rt_normal.c rt_object2.c \
			rt_normal2.c rt_object3.c rt_normal3.c

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
