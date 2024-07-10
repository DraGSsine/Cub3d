/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vert_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 07:51:20 by youchen           #+#    #+#             */
/*   Updated: 2024/07/10 19:25:52 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_vert_facing(t_vert_info *info, double ray_angle)
{
	info->down = ray_angle > 0 && ray_angle < M_PI;
	info->up = !info->down;
	info->right = ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI;
	info->left = !info->right;
}

void	init_vert_ray(t_vert_info *info, t_data *data, double ray_angle)
{
	player_vert_facing(info, ray_angle);
	info->x_intercept = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
	if (info->right)
		info->x_intercept += TILE_SIZE;
	info->y_intercept = data->player.y + (info->x_intercept - data->player.x)
		* tan(ray_angle);
	info->x_step = TILE_SIZE;
	if (info->left)
		info->x_step *= -1;
	info->y_step = fabs(TILE_SIZE * tan(ray_angle));
	if (info->up)
		info->y_step *= -1;
	info->next_vert_touch_x = info->x_intercept;
	info->next_vert_touch_y = info->y_intercept;
}

t_ray_vert	cast_vert_ray(double ray_angle, t_data *data)
{
	t_ray_vert	ray;
	t_vert_info	vert;

	init_vert_ray(&vert, data, ray_angle);
	ray.found_hit = 0;
	while (keep_checking(data, vert.next_vert_touch_x, vert.next_vert_touch_y))
	{
		if (hit_vert(data, vert))
		{
			ray.wall_hit_x = vert.next_vert_touch_x;
			ray.wall_hit_y = vert.next_vert_touch_y;
			ray.found_hit = 1;
			break ;
		}
		else
		{
			vert.next_vert_touch_x += vert.x_step;
			vert.next_vert_touch_y += vert.y_step;
		}
	}
	return (ray);
}
