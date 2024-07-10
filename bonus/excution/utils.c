/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:34:15 by youchen           #+#    #+#             */
/*   Updated: 2024/07/10 17:41:08 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int	hit_wall(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map_info.width_map * TILE_SIZE ||
		y < 0 || y >= data->map_info.height_map * TILE_SIZE)
		return (0);

	if (data->map_info.map[y / TILE_SIZE][x / TILE_SIZE] == '1')
		return (1);
	return (0);
}

double	block_color(double i)
{
	if (i == 1)
		return (0x757575);
	return (0x000000);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}
