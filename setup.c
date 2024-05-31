/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchen <youchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:52:30 by youchen           #+#    #+#             */
/*   Updated: 2024/05/31 16:59:29 by youchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_game(t_data *data)
{
	// int map[MAP_HEIGHT][MAP_WIDTH] = {
	// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
	// 	{1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
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
	data->player.rotation_speed = 10 * (M_PI / 180);
	data->player.move_speed = 10;
	data->player.fov = 30 * (M_PI / 180);
}
