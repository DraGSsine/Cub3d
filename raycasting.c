/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 07:51:11 by youchen           #+#    #+#             */
/*   Updated: 2024/07/08 19:52:39 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	distance(t_data *data, double x, double y, double found)
{
	if (found)
	{
		return (distance_between_points(data->player.x, data->player.y, x, y));		
	}
	return (INT_MAX);
}

void	short_distance(t_ray *ray, t_ray_horz horz,
		t_ray_vert vert, t_data *data)
{
	double	horz_distance;
	double	vert_distance;
	double	horz_hit;
	double	vert_hit;

	horz_hit = horz.found_hit;
	vert_hit = vert.found_hit;
	horz_distance = distance(data, horz.wall_hit_x, horz.wall_hit_y, horz_hit);
	vert_distance = distance(data, vert.wall_hit_x, vert.wall_hit_y, vert_hit);
	if (horz_distance < vert_distance)
	{
		ray->distance = horz_distance;
		ray->wall_hit_x = horz.wall_hit_x;
		ray->wall_hit_y = horz.wall_hit_y;
		ray->was_hit_vertical = 0;
	}
	else
	{
		ray->distance = vert_distance;
		ray->wall_hit_x = vert.wall_hit_x;
		ray->wall_hit_y = vert.wall_hit_y;
		ray->was_hit_vertical = 1;
	}
}


void	cast_ray(double ray_angle, t_data *data, t_ray *ray)
{
	t_ray_horz	horz;
	t_ray_vert	vert;

	horz = cast_horz_ray(ray_angle, data);
	vert = cast_vert_ray(ray_angle, data);
	short_distance(ray, horz, vert, data);
}

void	cast_all_rays(t_data *data, t_ray *ray)
{
	double	ray_angle;
	int		i;
	int		rays_num;

	i = 0;
	rays_num = data->map_info.rays_num;
	ray_angle = data->player.rotation_angle - (data->player.fov / 2);
	while (i < rays_num)
	{
		ray_angle = normalize_angle(ray_angle);
		ray[i].ray_angle = ray_angle;
		cast_ray(ray_angle, data, &ray[i]);
		ray_angle += data->player.fov / rays_num;
		i++;
	}
}
