/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:49:43 by ymomen            #+#    #+#             */
/*   Updated: 2024/06/30 10:15:19 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void set_retation(t_data *data)
{
    char c;
    
    c = data->player.position_side;
    if (c == 'N')
        data->player.rotation_angle = 3 * M_PI_2;
    else if (c == 'S')
        data->player.rotation_angle = M_PI_2;
    else if (c == 'W')
        data->player.rotation_angle = M_PI;
    else if (c == 'E')
        data->player.rotation_angle = 0;
    data->player.rotation_speed = 5 * (M_PI / 180);
	data->player.move_speed = 15;
	data->player.fov = 60 * (M_PI / 180);
    data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, data->map_info.window_width,
			data->map_info.window_height, "cub3d");
    // open_textures(data);
	data->img.img = mlx_new_image(data->mlx, data->map_info.window_width,
			data->map_info.window_height);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
}

void open_textures(t_data *data)
{
    t_map_info *mi;

    mi = &data->map_info;
    data->north_txt.img = mlx_xpm_file_to_image(data->mlx, mi->north_txt, &data->north_txt.img_width, &data->north_txt.img_height);
    data->south_txt.img = mlx_xpm_file_to_image(data->mlx,mi->south_txt, &data->south_txt.img_width, &data->south_txt.img_height);
    data->west_txt.img = mlx_xpm_file_to_image(data->mlx,mi->west_txt, &data->west_txt.img_width, &data->west_txt.img_height);
    data->east_txt.img = mlx_xpm_file_to_image(data->mlx,mi->east_txt, &data->east_txt.img_width, &data->east_txt.img_height);
    if (!data->north_txt.img || !data->south_txt.img || !data->west_txt.img || !data->east_txt.img)
    {
        free_map_info(data);
        error_and_exit("Error\nTexture not found\n", -9);
    }
    data->west_txt.addr = mlx_get_data_addr(data->west_txt.img, &data->west_txt.bits_per_pixel, &data->west_txt.line_length, &data->west_txt.endian);
    data->north_txt.addr = mlx_get_data_addr(data->north_txt.img, &data->north_txt.bits_per_pixel, &data->north_txt.line_length, &data->north_txt.endian);
    data->south_txt.addr = mlx_get_data_addr(data->south_txt.img, &data->south_txt.bits_per_pixel, &data->south_txt.line_length, &data->south_txt.endian);
    data->east_txt.addr = mlx_get_data_addr(data->east_txt.img, &data->east_txt.bits_per_pixel, &data->east_txt.line_length, &data->east_txt.endian);
    if (!data->north_txt.addr || !data->south_txt.addr || !data->west_txt.addr || !data->east_txt.addr)
    {
        free_map_info(data);
        error_and_exit("Error\nTexture not found\n", -9);
    }
}
