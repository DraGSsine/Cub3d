/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:09:54 by youchen           #+#    #+#             */
/*   Updated: 2024/07/10 12:39:44 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_offset_x(t_ray *ray)
{
	int	texture_offset_x;

	if (ray->was_hit_vertical)
		texture_offset_x = (int)ray->wall_hit_y % TILE_SIZE;
	else
		texture_offset_x = (int)ray->wall_hit_x % TILE_SIZE;
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
				mlx_put_pixel(data->imgs.map, x, y, data->map_info.ceiling_clr);
			else
				mlx_put_pixel(data->imgs.map, x, y, data->map_info.floor_clr);
			x++;
		}
		y++;
	}
}

void	draw_img(t_data *data, int x, int y, mlx_image_t *img)
{
	int	clr[4];
	int	color;
	int	i;

	i = (data->player.offset_x + data->player.offset_y * TILE_SIZE) * 4;
	clr[0] = img->pixels[i];
	clr[1] = img->pixels[i + 1];
	clr[2] = img->pixels[i + 2];
	clr[3] = img->pixels[i + 3];
	color = (clr[0] << 24 | clr[1] << 16 | clr[2] << 8 | clr[3]);
	mlx_put_pixel(data->imgs.map, x, y, color);
}

void	draw_wall(t_data *data, int i,
		int wall_height, t_ray *ray)
{
	int	start;
	int	end;
	int	y;
	int	distance;

	start = (data->map_info.window_height / 2) - (wall_height / 2);
	if (start < 0)
		start = 0;
	end = (data->map_info.window_height / 2) + (wall_height / 2);
	if (end > data->map_info.window_height)
		end = data->map_info.window_height;
	data->player.offset_x = get_offset_x(ray);
	y = start;
	while (y < end)
	{
		distance = y + (wall_height / 2) - (data->map_info.window_height / 2);
		data->player.offset_y = distance * ((float)TILE_SIZE / wall_height);
		if (ray->was_hit_vertical && ((ray->ray_angle >= 0 && ray->ray_angle < M_PI_2) || (ray->ray_angle >= 3 * M_PI_2 && ray->ray_angle < 2 * M_PI)))
			draw_img(data, i, y, data->imgs.east);
		else if (ray->was_hit_vertical && ray->ray_angle >= M_PI_2 && ray->ray_angle < 3 * M_PI_2)
			draw_img(data, i, y, data->imgs.west);
		else if (!ray->was_hit_vertical && ray->ray_angle >= 0 && ray->ray_angle < M_PI)
			draw_img(data, i, y, data->imgs.north);
		else if (!ray->was_hit_vertical && ray->ray_angle >= M_PI && ray->ray_angle < 2 * M_PI)
			draw_img(data, i, y, data->imgs.south);
		y++;
	}
}

void	render_walls(t_data *data, t_ray *rays)
{
	int		proj_dist;
	int		wall_height;
	int		i;
	double	ray_distance;

	clear_screen(data);
	proj_dist = (data->map_info.window_width / 2) / tan(data->player.fov / 2);
	i = 0;
	while (i < data->map_info.rays_num)
	{
		ray_distance = rays[i].distance * cos(data->player.rotation_angle
				- rays[i].ray_angle);
		wall_height = (TILE_SIZE / ray_distance) * proj_dist;
		draw_wall(data, i, wall_height, &rays[i]);
		i++;
	}
}
