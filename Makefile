SRC=render/main.c render/utils.c render/hooks.c render/player_mov.c render/dda_ray_cast.c render/render.c render/init_game.c \
	parse/get_next_line_utils.c parse/get_next_line.c parse/helpers.c \
          parse/parser_color.c parse/parser_ident01.c parse/parser_ident02.c parse/parser_main.c \
          parse/utils_free.c parse/utils_grid.c parse/utils_io.c parse/validate.c
OBJ=$(SRC:.c=.o)
FLAGS= -lmlx -framework OpenGL -framework AppKit 
NAME=cub

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(OBJ) $(FLAGS)  -o $(NAME)

parse/%.o : parse/%.c render/cube3d.h
	cc -Wall -Wextra -c $< -o $@

clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)

re: fclean all