# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 13:34:52 by youchen           #+#    #+#              #
#    Updated: 2024/07/08 17:13:54 by ymomen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name = cub3d
src= cub3d.c utils.c mlx_utils.c movement.c raycasting.c cast_vert_ray.c cast_horz_ray.c ray_utils.c render_walls.c parsing/parse_1.c parsing/utils.c parsing/list.c parsing/get_next_line_utils.c parsing/get_next_line.c parsing/utils_2.c parsing/parse_3.c parsing/parse_2.c parsing/ft_memset.c parsing/ft_strchr.c parsing/candelet.c parsing/parse_4.o
objs = $(src:.c=.o)
flags = -Wall -Wextra -Werror -fsanitize=address -Ofast
cc = cc -g
all: $(name)

$(name): $(objs)
	$(cc) $(flags) -o $(name) $(objs) ./MLX42/build/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

%.o: %.c
	$(cc) $(flags) -c $< -o $@

clean:
	rm -f $(objs)

fclean: clean
	rm -f $(name)
re: fclean all

