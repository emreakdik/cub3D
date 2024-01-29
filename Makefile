NAME = cub3D

CC = clang

CFLAGS = -O3 -Wall -Wextra -Werror -g

MLX = mlxopengl

LXFLAGS = -lmlx -framework OpenGL -framework AppKit

HEADER = cub3d.h

B_HEADER = cub3d_bonus.h

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
	libft/ft_atoi \
	libft/ft_memset \
	libft/ft_strlen \
	libft/ft_strspn \
	libft/ft_split \
	libft/ft_strjoin \
	libft/ft_strchr \
	libft/ft_memcpy \
	libft/ft_strdup \



FIL = $(addsuffix .c, $(addprefix files/, $(SRC)))

OBJ = $(FIL:.c=.o)

BIN = $(addsuffix .o, $(SRC))

.PHONY: all clean fclean re bonus test sqr bmp err inv norm

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[0;33mCompiling..."
	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(OBJ)
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning..."
	rm -rf $(OBJ) $(B_OBJ)
	rm -f bitmap.bmp
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean all


	./$(NAME)

test: re
	./$(NAME) maps/map.cub

sqr: re
	./$(NAME) maps/sqr.cub

bmp: re
	./$(NAME) maps/map.cub --save

err: re
	./$(NAME) maps/none

inv: re
	./$(NAME) maps/inv.cub

norm:
	norminette $(FIL) $(B_FIL) files/$(HEADER) bonus/$(B_HEADER)
