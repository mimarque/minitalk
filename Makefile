CLIENT=client

SERVER=server

CLIENT_C=client.c

SERVER_C=server.c

LIBFT=libft/libft.a

CC=gcc

CFLAGS=-Wall -Wextra -Werror

OBJ_DIR=obj

HDR=minitalk.h

SERVER_OBJ=$(SERVER:.c=.o)

CLIENT_OBJ=$(CLIENT:.c=.o)

LIB=-Llibft -lft

all: server client $(LIBFT)

$(LIBFT):
	make -C libft
	@echo "done libft"

$(OBJ_DIR):
	mkdir $@

server: $(SERVER_C)
	@echo "making server"
	$(CC) $(CFLAGS) $(LIB) $(SERVER_C) -o server

client:
	@echo "making server"
	$(CC) $(CFLAGS) $(LIB) $(CLIENT_C) -o client

clean:
	make -C libft $@

fclean: clean
	rm server
	rm client
	make -C libft $@

re: fclean all

.PHONY: all clean fclean re so