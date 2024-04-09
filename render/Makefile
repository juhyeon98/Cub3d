CC = cc
CFLAG = -Wall -Wextra -Werror -g3
LFLAG = -Lmlx -lmlx -framework OpenGL -framework AppKit
NAME = cub3D
SRCS = srcs/main.c \
	   srcs/render1.c \
	   srcs/render2.c \
	   srcs/event1.c \
	   srcs/event2.c
OBJS = $(SRCS:.c=.o)
MLXDIR = mlx
MLX = $(MLXDIR)/libmlx.dylib

# export DYLD_LIBRARY_PATH=/Users/juhyelee/Cub3d/render/mlx

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) $^ $(LFLAG) -o $@

$(MLX):
	make -C $(MLXDIR)

%.o: %.c
	$(CC) $(CFLAG) -g3 -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	make clean -C $(MLXDIR)
	rm -rf $(NAME)

re: fclean all
