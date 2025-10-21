SRC=main.c utils.c hooks.c stuff.c key_events.c player_mov.c raycasting.c render.c
OBJ=$(SRC:.c=.o)
FLAGS= -lmlx -framework OpenGL -framework AppKit 
NAME=cub

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(OBJ) $(FLAGS)  -o $(NAME)

%.o : %.c cube3d.h
	cc -Wall -Wextra -c $< -o $@

clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)

re: fclean all