CC=cc
CFLAG=-Wall -Wextra -Werror -c
LFLAG=-Lmlx -lmlx -framework OpenGL -framework AppKit
NAME=test
SRCS=test.c
OBJS=$(SRCS:.c=.o)
MLXDIR=mlx
MLX=$(MLXDIR)/libmlx.dylib

# export DYLD_LIBRARY_PATH=~/test/mlx

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) $^ $(LFLAG) -o $@

$(MLX):
	make -C $(MLXDIR)

%.o: %.c
	$(CC) $(CFLAG) $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	make clean -C $(MLXDIR)
	rm -rf $(NAME)

re: fclean all
