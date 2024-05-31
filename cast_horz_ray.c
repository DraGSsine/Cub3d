/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_horz_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchen <youchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 08:54:57 by youchen           #+#    #+#             */
/*   Updated: 2024/05/31 17:18:50 by youchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void draw_ray_line(int xFrom, int yFrom, int xTo, int yTo,int color , t_data *data)
{
    int dx = abs(xTo - xFrom);
    int dy = abs(yTo - yFrom);
    int sx = xFrom < xTo ? 1 : -1;
    int sy = yFrom < yTo ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;

    while (1)
    {
        my_mlx_pixel_put(data , xFrom, yFrom , color);
        if (xFrom == xTo && yFrom == yTo)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            xFrom += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            yFrom += sy;
        }
    }
}

void	setup_horz_ray(t_horz_info *info, t_data *data, double ray_angle)
{
	info->down = ray_angle > 0 && ray_angle < M_PI;
	info->up = !info->down;
	info->right = ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI;
	info->left = !info->right;
	info->y_intercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
	if (info->down)
		info->y_intercept += TILE_SIZE;
	info->x_intercept = data->player.x + (info->y_intercept - data->player.y)
		/ tan(ray_angle);
	info->y_step = TILE_SIZE;
	if (info->up)
		info->y_step *= -1;
	info->x_step = fabs(TILE_SIZE / tan(ray_angle));
	if (info->left)
		info->x_step *= -1;
	info->next_horz_touch_x = info->x_intercept;
	info->next_horz_touch_y = info->y_intercept;
}

t_ray_horz	cast_horz_ray(double ray_angle, t_data *data)
{
	t_horz_info	info;
	t_ray_horz	ray;

	setup_horz_ray(&info, data, ray_angle);
	while (keep_checking(data, info.next_horz_touch_x, info.next_horz_touch_y))
	{
		if (hit_horz(data, info))
		{
			ray.found_hit = 1;
			ray.wall_hit_x = info.next_horz_touch_x;
			ray.wall_hit_y = info.next_horz_touch_y;
			break ;
		}
		else
		{
			info.next_horz_touch_x += info.x_step;
			info.next_horz_touch_y += info.y_step;
		}
	}
	return (ray);
}
