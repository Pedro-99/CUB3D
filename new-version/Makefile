# Project Name
NAME = cub3d

# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# Directories
SRC_DIR = src
SRC_DIR_LIBFT = src/libft
SRC_DIR_GNL = src/get-next-line
OBJ_DIR = obj
INC_DIR = includes
MLX_DIR = MLX42

# Libft Source Files 
LIBFT_SRCS = $(SRC_DIR_LIBFT)/ft_strchr.c \
             $(SRC_DIR_LIBFT)/ft_strtrim.c \
             $(SRC_DIR_LIBFT)/ft_strncmp.c \
             $(SRC_DIR_LIBFT)/ft_strdup.c \
             $(SRC_DIR_LIBFT)/ft_memset.c \
             $(SRC_DIR_LIBFT)/ft_strlen.c \
             $(SRC_DIR_LIBFT)/ft_strlcpy.c \
             $(SRC_DIR_LIBFT)/ft_split.c \
             $(SRC_DIR_LIBFT)/ft_atoi.c \
             $(SRC_DIR_LIBFT)/ft_memcpy.c \

# GetNextLine Source Files 
GNL_SRCS = $(SRC_DIR_GNL)/get_next_line.c \
             $(SRC_DIR_GNL)/get_next_line_utils.c \

# Source Files (Core)
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/raycasting.c \
       $(SRC_DIR)/draw.c \
       $(SRC_DIR)/render.c \
       $(SRC_DIR)/hooks.c \
       $(SRC_DIR)/move.c \
       $(SRC_DIR)/parse.c \
       $(SRC_DIR)/utils.c

# Object Files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $(LIBFT_SRCS:$(SRC_DIR_LIBFT)/%.c=$(OBJ_DIR)/%.o) $(GNL_SRCS:$(SRC_DIR_GNL)/%.c=$(OBJ_DIR)/%.o)

# Header Files
HEADERS = $(INC_DIR)/cub3d.h

# MLX42 Library
MLX_LIB = $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS = -L$(MLX_DIR)/build -lmlx42 -ldl -lglfw -pthread -lm
INCLUDES = -I$(MLX_DIR)/include/MLX42 -I$(INC_DIR)

# Dependency Files
DEPS = $(OBJS:.o=.d)

# Rules
all: $(NAME)

# Link the executable
$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

# Compile source files from src/ into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# Compile source files from src/libft/ into object files
$(OBJ_DIR)/%.o: $(SRC_DIR_LIBFT)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# Compile source files from src/get-next-line/ into object files
$(OBJ_DIR)/%.o: $(SRC_DIR_GNL)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build MLX42
$(MLX_LIB):
	cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

# Clean object files and dependencies
clean:
	rm -rf $(OBJ_DIR)
	cd $(MLX_DIR) && rm -rf build

# Full clean (including executable)
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Include dependency files
-include $(DEPS)

