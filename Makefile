NAME = fractol
CC = cc  -g
SRC = fractol.c ./utils/ft_putstr_fd.c ./utils/error.c ./utils/ft_putchar_fd.c ./utils/ft_strlen.c ./utils/ft_strncmp.c ./utils/julia.c ./utils/color.c ./utils/events.c ./utils/tricorn.c ./utils/utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra  -I/usr/include -Imlx_linux -O3 -c $< -o $@
	
clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all