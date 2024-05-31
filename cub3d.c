/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchen <youchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:51:56 by youchen           #+#    #+#             */
/*   Updated: 2024/05/31 12:13:43 by youchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_map(t_data *data)
{
	for (int x = 0; x < data->map_info.window_width; x++)
	{
		for (int y = 0; y < data->map_info.window_height; y++)
		{
			int color = 0;
			if (data->map_info.map[y / TILE_SIZE][x / TILE_SIZE] == 1)
				color = 0x00FF0000;
			else
				color = 0x00000000;
			my_mlx_pixel_put(data, x, y, color);
		}
	}
}

void draw_line(t_data *data)
{
	int x = data->player.x;
	int y = data->player.y;
	int x2 = x + cos(data->player.rotation_angle) * 130;
	int y2 = y + sin(data->player.rotation_angle) * 130;
	int dx = abs(x2 - x);
	int dy = abs(y2 - y);
	int sx = x < x2 ? 1 : -1;
	int sy = y < y2 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (1)
	{
		my_mlx_pixel_put(data, x, y, 0x00FF0000);
		if (x == x2 && y == y2)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y += sy;
		}
	}
}

void draw_player(t_data *data)
{
	t_player player;

	player = data->player;
	int i = 0;
	while (i < 10)
	{
		int j = 0;
		while (j < 10)
		{
			my_mlx_pixel_put(data, (player.x + i), (player.y + j), 0x0000FF00);
			j++;
		}
		i++;
	}
}

void	draw(t_data *data)
{
	t_ray	rays[MAP_WIDTH * TILE_SIZE];

	draw_map(data);
	draw_player(data);
	cast_all_rays(data, rays);
	// render_walls(data, rays);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

int	main(void)
{
	t_data	data;

	init_game(&data);
	draw(&data);
	mlx_hook(data.mlx_win, 2, 0, movement, &data);
	mlx_hook(data.mlx_win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
