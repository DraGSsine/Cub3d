/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vert_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchen <youchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 08:47:12 by youchen           #+#    #+#             */
/*   Updated: 2024/05/30 13:21:16 by youchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_vert_ray(t_vert_info *info, t_data *data, double ray_angle)
{
	info->down = ray_angle > 0 && ray_angle < M_PI;
	info->up = !info->down;
	info->right = ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI;
	info->left = !info->right;

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
	t_vert_info	info;
	t_ray_vert	ray;

	ray.found_hit = 0;
	ray.wall_hit_x = 0;
	ray.wall_hit_y = 0;
	setup_vert_ray(&info, data, ray_angle);
	while (keep_checking(data, info.next_vert_touch_x, info.next_vert_touch_y))
	{
		if (hit_vert(data, info))
		{
			ray.wall_hit_x = info.next_vert_touch_x;
			ray.wall_hit_y = info.next_vert_touch_y;
			ray.found_hit = 1;
			break ;
		}
		else
		{
			info.next_vert_touch_x += info.x_step;
			info.next_vert_touch_y += info.y_step;
		}
	}
	return (ray);
}
