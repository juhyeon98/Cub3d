# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/28 11:02:51 by juhyelee          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/04/16 16:45:53 by juhyelee         ###   ########.fr        #
=======
#    Updated: 2024/04/16 18:14:19 by juhyelee         ###   ########.fr        #
>>>>>>> cd40bbd970e40683fccf027e9bba3798f3abc65d
#                                                                              #
# **************************************************************************** #

LIBFTDIR	= libft
LIBFT		= ${LIBFTDIR}/libft.a
MLXDIR		= mlx
MLX			= $(MLXDIR)/libmlx.dylib

MAN_DIR		= mandatory
MAN_INCS	= ${MAN_DIR}includes
MAN_SDIR	= ${MAN_DIR}/srcs
MAN_SRCS	= ${MAN_SDIR}/main.c \
			  ${MAN_SDIR}/error.c \
			  ${MAN_SDIR}/get_line.c \
			  ${MAN_SDIR}/rsrc1.c \
			  ${MAN_SDIR}/rsrc2.c \
			  ${MAN_SDIR}/map1.c \
			  ${MAN_SDIR}/map2.c \
			  ${MAN_SDIR}/map3.c \
			  ${MAN_SDIR}/window.c \
			  ${MAN_SDIR}/render1.c \
			  ${MAN_SDIR}/render2.c \
			  ${MAN_SDIR}/event1.c \
			  ${MAN_SDIR}/event2.c
MAN_OBJS	= ${MAN_SRCS:.c=.o}

BNS_DIR		= bonus

MK			= make -C
RM			= rm -rf
CC			= cc
CFLAG		= -Wall -Wextra -Werror -I${INCS}
LFLAG		= -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit

NAME		= cub3D
BONUS		= cub3D_bonus

.PHONY		: all bonus clean fclean re

all			: ${NAME}
bonus		: ${BONUS}
clean		:
	${RM} ${OBJS}
	${MK} ${LIBFTDIR} clean
fclean		:
	${RM} ${OBJS}
	${RM} ${NAME}
	${MK} ${LIBFTDIR} fclean
	${MK} ${MLXDIR} clean
re			: fclean all

${NAME}		: ${MAN_OBJS} ${LIBFT} ${MLX}
	${CC} ${LFLAG} $^ -o $@
${BONUS}	: ${MAN_OBJS} ${LIBFT} ${MLX}
	${CC} ${LFLAG} $^ -o $@
${LIBFT}	:
	${MK} ${LIBFTDIR}
$(MLX)		:
	make -C $(MLXDIR)
%.o			: %.c
	${CC} ${CFLAG} $< -o $@ -c
