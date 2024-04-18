# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/28 11:02:51 by juhyelee          #+#    #+#              #
#    Updated: 2024/04/18 17:15:46 by juhyelee         ###   ########.fr        #
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
BNS_INCS	= ${BNS_DIR}/includes
BNS_SDIR	= ${BNS_DIR}/srcs
BNS_SRCS	= ${BNS_SDIR}/main_bonus.c \
			  ${BNS_SDIR}/error_bonus.c \
			  ${BNS_SDIR}/get_line_bonus.c \
			  ${BNS_SDIR}/rsrc1_bonus.c \
			  ${BNS_SDIR}/rsrc2_bonus.c \
			  ${BNS_SDIR}/map1_bonus.c \
			  ${BNS_SDIR}/map2_bonus.c \
			  ${BNS_SDIR}/map3_bonus.c \
			  ${BNS_SDIR}/map4_bonus.c \
			  ${BNS_SDIR}/window1_bonus.c \
			  ${BNS_SDIR}/window2_bonus.c \
			  ${BNS_SDIR}/render1_bonus.c \
			  ${BNS_SDIR}/render2_bonus.c \
			  ${BNS_SDIR}/minimap_bonus.c \
			  ${BNS_SDIR}/event1_bonus.c \
			  ${BNS_SDIR}/event2_bonus.c \
			  ${BNS_SDIR}/fist_bonus.c
BNS_OBJS	= ${BNS_SRCS:.c=.o}

MK			= make -C
RM			= rm -rf
CC			= cc
CFLAG		= -Wall -Wextra -Werror
LFLAG		= -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit

NAME		= cub3D
BONUS		= cub3D_bonus

.PHONY		: all bonus clean fclean re

all			: ${NAME}
bonus		: ${BONUS}
clean		:
	${RM} ${MAN_OBJS}
	${RM} ${BNS_OBJS}
	${MK} ${LIBFTDIR} clean
fclean		: clean
	${RM} ${NAME}
	${RM} ${BONUS}
	${MK} ${LIBFTDIR} fclean
	${MK} ${MLXDIR} clean
re			: fclean all

${NAME}		: ${MAN_OBJS} ${LIBFT} ${MLX}
	${CC} ${LFLAG} -I${MAN_INCS} $^ -o $@
${BONUS}	: ${BNS_OBJS} ${LIBFT} ${MLX}
	${CC} ${LFLAG} -I${BNS_INCS} $^ -o $@
${LIBFT}	:
	${MK} ${LIBFTDIR}
$(MLX)		:
	make -C $(MLXDIR)
%.o			: %.c
	${CC} ${CFLAG} $< -o $@ -c
