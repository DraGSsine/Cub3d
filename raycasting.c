/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchen <youchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 06:46:42 by youchen           #+#    #+#             */
/*   Updated: 2024/05/31 06:43:02 by youchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	short_dist(t_ray_horz *ray_horz, t_ray_vert *ray_vert,
		int horz_distance, int vert_distance)
{
	t_ray	ray;

	if (vert_distance < horz_distance)
	{
		ray.distance = vert_distance;
		ray.wall_hit_x = ray_vert->wall_hit_x;
		ray.wall_hit_y = ray_vert->wall_hit_y;
		ray.was_hit_vertical = 1;
	}
	else
	{
		ray.distance = horz_distance;
		ray.wall_hit_x = ray_horz->wall_hit_x;
		ray.wall_hit_y = ray_horz->wall_hit_y;
		ray.was_hit_vertical = 0;
	}
	return (ray);
}

void	cast_ray(double ray_angle, t_data *data, t_ray *ray)
{
	t_ray_horz	ray_horz;
	t_ray_vert	ray_vert;
	int			horz_distance;
	int			vert_distance;
	t_ray		ray_info;

	ray_horz = cast_horz_ray(ray_angle, data);
	ray_vert = cast_vert_ray(ray_angle, data);
	if (ray_horz.found_hit)
		horz_distance = distance_between_points(data->player.x, data->player.y,
				ray_horz.wall_hit_x, ray_horz.wall_hit_y);
	else
		horz_distance = INT_MAX;

	if (ray_vert.found_hit)
		vert_distance = distance_between_points(data->player.x, data->player.y,
				ray_vert.wall_hit_x, ray_vert.wall_hit_y);
	else
		vert_distance = INT_MAX;
	ray_info = short_dist(&ray_horz, &ray_vert, horz_distance, vert_distance);
	ray->distance = ray_info.distance;
	ray->wall_hit_x = ray_info.wall_hit_x;
	ray->wall_hit_y = ray_info.wall_hit_y;
	ray->was_hit_vertical = ray_info.was_hit_vertical;

}

void	cast_all_rays(t_data *data, t_ray *rays)
{
	double	ray_angle;
	int		rays_num;
	int		i;

	i = 0;
	data->player.rotation_angle = normalize_angle(data->player.rotation_angle);
	rays_num = data->map_info.rays_num;
	ray_angle = data->player.rotation_angle - (data->player.fov / 2);
	while (i < rays_num)
	{
		cast_ray(ray_angle, data, &rays[i]);
		ray_angle += data->player.fov / rays_num;
		i++;
	}
}
