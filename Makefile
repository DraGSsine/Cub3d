name = cub3d
objs = cub3d.o utils.o mlx_utils.o movement.o setup.o raycasting.o cast_vert_ray.o cast_horz_ray.o ray_utils.o render_walls.o
flags = -Wall -Wextra -Werror
cc = gcc -g
all: $(name)

$(name): $(objs)
	$(cc) $(flags) -o $(name) $(objs) -lmlx -framework OpenGL -framework AppKit

clean:
	rm -f $(objs)

fclean: clean
	rm -f $(name)
re: fclean all

