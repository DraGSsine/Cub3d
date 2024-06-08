# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 13:34:52 by youchen           #+#    #+#              #
#    Updated: 2024/06/08 14:17:13 by ymomen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name = cub3d
objs = cub3d.o utils.o mlx_utils.o movement.o setup.o raycasting.o cast_vert_ray.o cast_horz_ray.o ray_utils.o render_walls.o
flags = -Wall -Wextra -Werror -g -fsanitize=address
cc = gcc -g
all: $(name)

$(name): $(objs)
	$(cc) $(flags) -o $(name) $(objs) -lmlx -framework OpenGL -framework AppKit

clean:
	rm -f $(objs)

fclean: clean
	rm -f $(name)
re: fclean all

