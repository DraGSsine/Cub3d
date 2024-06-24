/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:52:30 by youchen           #+#    #+#             */
/*   Updated: 2024/06/24 19:36:12 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "textures.h"


void	init_game(t_data *data)
{
	// int map[MAP_HEIGHT][MAP_WIDTH] = {
	// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1 ,0, 0, 0, 0,1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,1},
	// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1}};

	// int map[MAP_HEIGHT][MAP_WIDTH] = {
	// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	// int i = -1;
	// while (++i < MAP_HEIGHT)
	// {
	// 	int j = -1;
	// 	while (++j < MAP_WIDTH)
	// 		data->map_info.map[i][j] = map[i][j];
	// }
	data->map_info.window_width = data->map_info.width_map * TILE_SIZE;
	data->map_info.window_height = data->map_info.height_map * TILE_SIZE;
	data->map_info.rays_num = data->map_info.width_map * TILE_SIZE;
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, data->map_info.window_width,
			data->map_info.window_height, "cub3d");
	data->img = mlx_new_image(data->mlx, data->map_info.window_width,
			data->map_info.window_height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	// data->player.x = data->map_info.window_width / 2;
	// data->player.y = data->map_info.window_height / 2;
	// data->player.rotation_angle = 90 * (M_PI / 180);
	data->player.rotation_angle = (data->player.position_side == 'N') ? 270 * (M_PI / 180) : (data->player.position_side == 'S') ? 90 * (M_PI / 180) : (data->player.position_side == 'W') ? 180 * (M_PI / 180) : 0;
	data->player.rotation_speed = 5 * (M_PI / 180);
	data->player.move_speed = 10;
	data->player.fov = 60 * (M_PI / 180);
	data->map_info.texture[0]= (unsigned int *) REDBRICK_TEXTURE;
	data->map_info.texture[1]= (unsigned int *) PURPLESTONE_TEXTURE;
	data->map_info.texture[2]= (unsigned int *) MOSSYSTONE_TEXTURE;
	data->map_info.texture[3]= (unsigned int *) GRAYSTONE_TEXTURE;
	data->map_info.texture[4]= (unsigned int *) COLORSTONE_TEXTURE;
	data->map_info.texture[5]= (unsigned int *) WOOD_TEXTURE;
	data->map_info.texture[6]= (unsigned int *) EAGLE_TEXTURE;
	data->map_info.texture[7]= (unsigned int *) BLUESTONE_TEXTURE;
}
