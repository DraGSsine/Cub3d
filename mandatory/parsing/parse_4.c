/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:49:43 by ymomen            #+#    #+#             */
/*   Updated: 2024/07/10 19:28:19 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void set_retation(t_data *data)
{
    char c;
    
    c = data->player.position_side;
    if (c == 'N')
        data->player.rotation_angle = M_PI_2;
    else if (c == 'S')
        data->player.rotation_angle = 3 * M_PI_2;
    else if (c == 'W')
        data->player.rotation_angle = M_PI;
    else if (c == 'E')
        data->player.rotation_angle = 0;
    data->player.rotation_speed = RETATION_SPEED * (M_PI / 180);
	data->player.move_speed = MOVE_SPEED;
	data->player.fov = 60 * (M_PI / 180);
    data->imgs.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", false);
    data->imgs.map = mlx_new_image(data->imgs.mlx, WIN_WIDTH, WIN_HEIGHT);
    open_textures(data);
}

void open_textures(t_data *data)
{
    mlx_texture_t *texture;

    texture = mlx_load_png(data->map_info.north_txt);
    if (!texture)
    {
        free_map_info(data);
        error_and_exit("Error\nTexture not found\n", -9);
    }
    data->imgs.north = mlx_texture_to_image(data->imgs.mlx ,texture);
    texture = mlx_load_png(data->map_info.south_txt);
       if (!texture)
    {
        free_map_info(data);
        error_and_exit("Error\nTexture not found\n", -9);
    }
    data->imgs.south = mlx_texture_to_image(data->imgs.mlx ,texture);
    texture = mlx_load_png(data->map_info.west_txt);
       if (!texture)
    {
        free_map_info(data);
        error_and_exit("Error\nTexture not found\n", -9);
    }
    data->imgs.west = mlx_texture_to_image(data->imgs.mlx ,texture);
    texture = mlx_load_png(data->map_info.east_txt);
       if (!texture)
    {
        free_map_info(data);
        error_and_exit("Error\nTexture not found\n", -9);
    }
    data->imgs.east = mlx_texture_to_image(data->imgs.mlx ,texture);
    if (!data->imgs.north || !data->imgs.south || !data->imgs.west || !data->imgs.east)
    {
        free_map_info(data);
        error_and_exit("Error\nTexture not found\n", -9);
    }
}
