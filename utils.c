/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchen <youchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:34:15 by youchen           #+#    #+#             */
/*   Updated: 2024/05/31 13:55:45 by youchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	distance_between_points(int x1, int y1, int x2, int y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

int	hit_wall(t_data *data, int x, int y)
{
	if (data->map_info.map[y / TILE_SIZE][x / TILE_SIZE] == 1)
		return (1);
	return (0);
}

int	block_color(int i)
{
	if (i == 1)
		return (0x757575);
	return (0x000000);
}

float	normalize_angle(double angle)
{
    angle = remainder(angle, 2 * M_PI);
    if (angle < 0)
        angle = (2 * M_PI) + angle;
    return angle;
}
