NAME = libft.a
FLAG = -Wall -Wextra -Werror
SRC = $(shell find . ! -name "ft_lst*.c" -name "ft_*.c")
BONUS = $(shell find . -name "ft_lst*.c")
OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME):
	@gcc $(FLAG) -c $(SRC) 2> /dev/null
	@ar rc $(NAME) *.o 2> /dev/null
bonus:
	@gcc $(FLAG) -c $(BONUS) 2> /dev/null
	@ar rc $(NAME) *.o 2> /dev/null
clean:
	@/bin/rm -f  *.o 2> /dev/null
fclean: clean
	@/bin/rm -f $(NAME) 2> /dev/null
re: fclean all

.PHONY: all bonus clean fclean re