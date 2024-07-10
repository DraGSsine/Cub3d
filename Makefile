# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/01 13:34:52 by youchen           #+#    #+#              #
#    Updated: 2024/07/10 19:19:14 by ymomen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name = cub3D
name_bonus = cub3D_bonus
src= mandatory/excution/cub3d.c mandatory/excution/utils.c mandatory/excution/movement.c mandatory/excution/raycasting.c mandatory/excution/cast_vert_ray.c mandatory/excution/cast_horz_ray.c mandatory/excution/ray_utils.c mandatory/excution/render_walls.c mandatory/parsing/parse_1.c mandatory/parsing/utils.c mandatory/parsing/list.c mandatory/parsing/get_next_line_utils.c mandatory/parsing/get_next_line.c mandatory/parsing/utils_2.c mandatory/parsing/parse_3.c mandatory/parsing/parse_2.c mandatory/parsing/ft_memset.c mandatory/parsing/ft_strchr.c mandatory/parsing/candelet.c mandatory/parsing/parse_4.c
src_bonus= bonus/excution/cub3d.c bonus/excution/utils.c bonus/excution/movement.c bonus/excution/raycasting.c bonus/excution/cast_vert_ray.c bonus/excution/cast_horz_ray.c bonus/excution/ray_utils.c bonus/excution/render_walls.c bonus/parsing/parse_1.c bonus/parsing/utils.c bonus/parsing/list.c bonus/parsing/get_next_line_utils.c bonus/parsing/get_next_line.c bonus/parsing/utils_2.c bonus/parsing/parse_3.c bonus/parsing/parse_2.c bonus/parsing/ft_memset.c bonus/parsing/ft_strchr.c bonus/parsing/candelet.c bonus/parsing/parse_4.c
objs = $(src:.c=.o)
objs_bonus = $(src_bonus:.c=.o)
flags = -Wall -Wextra -Werror -fsanitize=address -Ofast
cc = cc -g
all: $(name)

$(name): $(objs)
	$(cc) $(flags) -o $(name) $(objs) ./MLX42/build/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

%.o: %.c mandatory/cub3d.h
	$(cc) $(flags) -c $< -o $@

bonus:  $(objs_bonus)
	$(cc) $(flags) -o $(name_bonus) $(objs_bonus) ./MLX42/build/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

clean:
	rm -f $(objs) $(objs_bonus)

fclean: clean
	rm -f $(name) $(name_bonus)
re: fclean all

