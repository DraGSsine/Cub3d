# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 13:34:52 by youchen           #+#    #+#              #
#    Updated: 2024/06/24 18:34:26 by ymomen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name = cub3d
srcs = cub3d.c utils.c mlx_utils.c movement.c setup.c raycasting.c cast_vert_ray.c cast_horz_ray.c ray_utils.c render_walls.c parsing/pars.c parsing/utils.c parsing/list.c parsing/get_next_line_utils.c parsing/get_next_line.c parsing/utils_2.c
objs = $(srcs:.c=.o)
flags = -Wall -Wextra -Werror #-O3 -fsanitize=address
cc = gcc #-g
all: $(name)

$(name): $(objs)
	$(cc) $(flags) -o $(name) $(objs) -lmlx -framework OpenGL -framework AppKit

%.o:%.c
	$(cc) $(flags) -c $< -o $@

clean:
	rm -f $(objs)

fclean: clean
	rm -f $(name)
re: fclean all

