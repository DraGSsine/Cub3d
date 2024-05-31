/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchen <youchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:42:30 by youchen           #+#    #+#             */
/*   Updated: 2024/05/31 12:08:17 by youchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color_wall(int was_hit_vertical)
{
	if (was_hit_vertical)
		return (0x2e4e5e);
	return (0x3f5e6d);
}

void	clear_screen(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_info.window_height)
	{
		x = 0;
		while (x < data->map_info.window_width)
		{
			if (y < data->map_info.window_height / 2)
				my_mlx_pixel_put(data, x, y, 0x87CEEB);
			else
				my_mlx_pixel_put(data, x, y, 0x684132);
			x++;
		}
		y++;
	}
}

void	draw_wall(t_data *data, int i, int wall_strip_height)
{
	int	start;
	int	end;

	start = (data->map_info.window_height / 2) - (wall_strip_height / 2);
	end = (data->map_info.window_height / 2) + (wall_strip_height / 2);
	while (start < end)
	{
		my_mlx_pixel_put(data, i, start, 0xc0FcF0);
		start++;
	}

}


void	render_walls(t_data *data, t_ray *rays)
{
	int	proj_dist;
	int	wall_strip_height;
	int	i;

	i = -1;
	// clear_screen(data);
	while (++i < data->map_info.rays_num)
	{
		proj_dist = (data->map_info.window_width / 2) / tan(data->player.rotation_angle / 2);
		wall_strip_height = (TILE_SIZE / rays[i].distance) * proj_dist;
		if (wall_strip_height > data->map_info.window_height)
			wall_strip_height = data->map_info.window_height;
		draw_wall(data, i, wall_strip_height);
	}
}
