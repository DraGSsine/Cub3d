/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:09:54 by youchen           #+#    #+#             */
/*   Updated: 2024/07/06 21:09:29 by ymomen           ###   ########.fr       */
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
				mlx_put_pixel(data->imgs.map, x, y, data->map_info.ceiling_clr);
			else
				mlx_put_pixel(data->imgs.map, x, y, data->map_info.floor_clr);
			x++;
		}
		y++;
	}
}

void	draw_wall(t_data *data, int i,
		int wall_height, int was_hit_vertical)
{
	int	start;
	int	end;
	int	color;
	int	y;


	if (wall_height > data->map_info.window_height)
		wall_height = data->map_info.window_height;
	start = (data->map_info.window_height / 2) - (wall_height / 2);
	end = (data->map_info.window_height / 2) + (wall_height / 2);
	color = get_color_wall(was_hit_vertical);
	y = 0;
	while( y < start)
	{
		mlx_put_pixel(data->imgs.map, i, y, data->map_info.ceiling_clr);
		y++;
	}
	while (y < end)
	{
		mlx_put_pixel(data->imgs.map, i, y, color);
		y++;
	}
	while (y < data->map_info.window_height)
	{
		mlx_put_pixel(data->imgs.map, i, y, data->map_info.floor_clr);
		y++;
	}
}

void	render_walls(t_data *data, t_ray *rays)
{
	int		proj_dist;
	int		wall_height;
	int		i;
	double	ray_distance;

	// clear_screen(data);
	proj_dist = (data->map_info.window_width / 2) / tan(data->player.fov / 2) ;
	i = 0;
	while (i < data->map_info.rays_num)
	{
		ray_distance = rays[i].distance * cos(data->player.rotation_angle
			- rays[i].ray_angle );
		wall_height = (TILE_SIZE / ray_distance) * proj_dist;
		draw_wall(data, i, wall_height, rays[i].was_hit_vertical);
		i++;
	}
}
