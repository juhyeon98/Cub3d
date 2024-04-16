# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/28 11:02:51 by juhyelee          #+#    #+#              #
#    Updated: 2024/04/16 11:46:04 by juhyelee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# export DYLD_LIBRARY_PATH=/Users/juhyelee/Cub3d/mlx
# export DYLD_LIBRARY_PATH=/Users/taeoh/Cub3d/mlx

LIBFTDIR = libft
LIBFT = ${LIBFTDIR}/libft.a
MLXDIR = mlx
MLX = $(MLXDIR)/libmlx.dylib

INCS = includes
SRCS = srcs/main.c \
	   srcs/error.c \
	   srcs/get_line.c \
	   srcs/rsrc1.c \
	   srcs/rsrc2.c \
	   srcs/map1.c \
	   srcs/map2.c \
	   srcs/map3.c \
	   srcs/window.c \
	   srcs/render1.c \
	   srcs/render2.c \
	   srcs/event1.c \
	   srcs/event2.c
OBJS = ${SRCS:.c=.o}

MK = make -C
RM = rm -rf
CC = cc
CFLAG = -Wall -Wextra -Werror -I${INCS}
LFLAG = -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit

NAME = cub3D

.PHONY : all clean fclean re

all : ${NAME}
clean :
	${RM} ${OBJS}
	${MK} ${LIBFTDIR} clean
fclean :
	${RM} ${OBJS}
	${RM} ${NAME}
	${MK} ${LIBFTDIR} fclean
	${MK} ${MLXDIR} clean
re : fclean all

${NAME} : ${OBJS} ${LIBFT} ${MLX}
	${CC} ${LFLAG} $^ -o $@
${LIBFT} :
	${MK} ${LIBFTDIR}
$(MLX):
	make -C $(MLXDIR)
%.o : %.c
	${CC} ${CFLAG} $< -o $@ -c
