/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:09:54 by youchen           #+#    #+#             */
/*   Updated: 2024/06/09 15:34:46 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color_wall(t_ray *ray )
{
	int texture_offset_x;
	
	if (ray->was_hit_vertical)
		texture_offset_x =  (int)ray->wall_hit_y %  TILE_SIZE;
	else
		texture_offset_x =  (int)ray->wall_hit_x %  TILE_SIZE;
	return (texture_offset_x);
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

void	draw_wall(t_data *data, int i,
		int wall_strip_height, t_ray *ray)
{
	int	start;
	int	end;
	int	texture_offset_x;
	int texture_offset_y;
	unsigned int	color;
	int distance;
	int	y;
    
	start = (data->map_info.window_height / 2) - (wall_strip_height / 2);
	if (start < 0)
		start = 0;
	end = (data->map_info.window_height / 2) + (wall_strip_height / 2);
    if (end > data->map_info.window_height)
		end = data->map_info.window_height;
	texture_offset_x = get_color_wall(ray);
	y = start;
	while (y < end)
	{
		distance = y + (wall_strip_height / 2) - (data->map_info.window_height / 2);
		texture_offset_y = distance * ((double)TEXTURE_HEIGHT / wall_strip_height);
		color = data->map_info.texture[(TEXTURE_WIDTH * texture_offset_y) + texture_offset_x];
		my_mlx_pixel_put(data, i, y, color);
		y++;
	}
}

void	render_walls(t_data *data, t_ray *rays)
{
	int		proj_dist;
	int		wall_strip_height;
	int		i;
	double	ray_distance;

	clear_screen(data);

	proj_dist = (data->map_info.window_width / 2) / tan(data->player.fov / 2);

	i = 0;
	while  (i< data->map_info.rays_num)
	{
		ray_distance = rays[i].distance * cos(rays[i].ray_angle
				- data->player.rotation_angle);
		wall_strip_height = (TILE_SIZE / ray_distance) * proj_dist;
		draw_wall(data, i, wall_strip_height, &rays[i]);
		i++;
	}
}
