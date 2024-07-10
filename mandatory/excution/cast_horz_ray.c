/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_horz_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 07:51:28 by youchen           #+#    #+#             */
/*   Updated: 2024/07/10 17:40:16 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_horz_facing(t_horz_info *info, double ray_angle)
{
	info->down = ray_angle > 0 && ray_angle < M_PI;
	info->up = !info->down;
	info->right = ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI;
	info->left = !info->right;
}

void	init_horz_ray(t_horz_info *info, t_data *data, double ray_angle)
{
	player_horz_facing(info, ray_angle);
	info->y_intercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
	if (info->down)
		info->y_intercept += TILE_SIZE;
	info->x_intercept = data->player.x + (info->y_intercept - data->player.y)
		/ tan(ray_angle);
	info->y_step = TILE_SIZE;
	if (info->up)
		info->y_step *= -1;
	info->x_step = fabs(TILE_SIZE / tan(ray_angle));
	if (info->left && info->x_step > 0)
		info->x_step *= -1;
	info->next_horz_touch_x = info->x_intercept;
	info->next_horz_touch_y = info->y_intercept;
}


t_ray_horz	cast_horz_ray(double ray_angle, t_data *data)
{
	t_horz_info	horz;
	t_ray_horz	ray;

	init_horz_ray(&horz, data, ray_angle);
	ray.found_hit = 0;
	while (keep_checking(data, horz.next_horz_touch_x, horz.next_horz_touch_y))
	{
		if (hit_horz(data, horz))
		{
			ray.wall_hit_x = horz.next_horz_touch_x;
			ray.wall_hit_y = horz.next_horz_touch_y;
			ray.found_hit = 1;
			break ;
		}
		else
		{
			horz.next_horz_touch_x += horz.x_step;
			horz.next_horz_touch_y += horz.y_step;
		}
	}
	return (ray);
}
