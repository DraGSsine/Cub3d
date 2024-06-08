/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:52:30 by youchen           #+#    #+#             */
/*   Updated: 2024/06/08 16:16:14 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void   init_texture(t_data *data)
{
	int x;
	int y;
	
	x = 0;
	while (x < TEXTURE_WIDTH)
	{
		y = 0;
		while (y < TEXTURE_HEIGHT)
		{
			if ( x % 8 && y % 8)
				data->map_info.texture[(TEXTURE_WIDTH * y) + x] = 0x000000FF;
			else
				data->map_info.texture[(TEXTURE_WIDTH * y) + x] = 0xFF0000FF;
			y++;
		}
		x++;
	}
	
}

void	init_game(t_data *data)
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

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
	int i = -1;
	while (++i < MAP_HEIGHT)
	{
		int j = -1;
		while (++j < MAP_WIDTH)
			data->map_info.map[i][j] = map[i][j];
	}
	data->map_info.window_width = MAP_WIDTH * TILE_SIZE;
	data->map_info.window_height = MAP_HEIGHT * TILE_SIZE;
	data->map_info.rays_num = MAP_WIDTH * TILE_SIZE;
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, data->map_info.window_width,
			data->map_info.window_height, "cub3d");
	data->img = mlx_new_image(data->mlx, data->map_info.window_width,
			data->map_info.window_height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->player.x = data->map_info.window_width / 2;
	data->player.y = data->map_info.window_height / 2;
	data->player.rotation_angle = 90 * (M_PI / 180);
	data->player.rotation_speed = 5 * (M_PI / 180);
	data->player.move_speed = 10;
	data->player.fov = 60 * (M_PI / 180);
	data->map_info.texture = (unsigned int *)malloc(sizeof(unsigned int) * TEXTURE_WIDTH * TEXTURE_HEIGHT);
	init_texture(data);
}
