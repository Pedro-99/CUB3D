CC = cc -g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L/usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

SRC_FILES =	./render.c ./math_utils.c ./main.c ./events.c  ./init.c ./shapes.c ./mlx_utils.c \
			./render_utils.c


OBJ_FILES = $(SRC_FILES:.c=.o)

HEADER = cub3d.h

NAME = cub3d 

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJ_FILES) -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

