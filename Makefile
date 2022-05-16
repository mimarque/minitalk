SRC_FILES:=$(wildcard *.c)

NAME=libftprintf.a

LIBFT=libft/libft.a

CC=gcc

CFLAGS=-Wall -Wextra -Werror

OBJ_DIR=obj

HDR=ft_printf.h

SRC_NAMES=$(patsubst %.c,%.o,$(SRC_FILES))

SRC_NAMES_O=$(addprefix $(OBJ_DIR)/, $(SRC_NAMES))

$(OBJ_DIR):
	mkdir $@

%.o: %.c $(HDR) $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)/$@ 

$(LIBFT):
	make -C libft

$(NAME): $(LIBFT) $(OBJ_DIR) $(SRC_NAMES)
	cp libft/libft.a $@
	ar -rcs $@ $(SRC_NAMES_O)

all: $(NAME)

bonus: all

clean:
	rm -rf obj/
	make -C libft $@

fclean: clean
	rm -f libftprintf.a
	make -C libft $@

re: fclean all

.PHONY: all clean fclean re so