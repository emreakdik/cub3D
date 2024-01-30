NAME = cub3D

CC = clang

CFLAGS = -O3 -Wall -Wextra -Werror -g

MLX = includes/mlxopengl

LXFLAGS = -lmlx -framework OpenGL -framework AppKit

HEADER = includes/cub3d.h

LIBFT = includes/libft

SRC = cub3d \
      tools \
		parse/file_management \
		parse/file_separate \
		parse/map_checks \
		parse/map_positioning \
		screen/screen_col \
		screen/screen \
		screen/create_table \
		hook/key \
		hook/hook \

FIL = $(addsuffix .c, $(addprefix src/, $(SRC)))

OBJ = $(FIL:.c=.o)

BIN = $(addsuffix .o, $(SRC))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n🧙‍♂️ Wizard: Conjuring the components of the realm..."
	@make -C $(MLX) 2> /dev/null
	@make -C $(LIBFT) 2> /dev/null
	@$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(OBJ) -L $(LIBFT) -lft 2> /dev/null
	@echo "🏰 Castle: The stronghold is fortified, $(NAME) stands tall!"

clean:
	@echo "🌊 River Spirit: Cleansing the artifacts..."
	@make clean -C $(MLX)
	@make fclean -C $(LIBFT)
	rm -rf $(OBJ)
	@echo "🍃 Winds: The remnants have been swept away!"

fclean: clean
	@echo "🔥 Dragon's Breath: Incinerating the fortress..."
	rm -f $(NAME)
	@echo "🌑 Eclipse: Nothing remains but shadows..."

re: fclean all