/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:28:30 by youchen           #+#    #+#             */
/*   Updated: 2024/06/08 22:53:27 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	front_move(t_data *data)
{
	int	x;
	int	y;

	x = data->player.move_speed * cos(data->player.rotation_angle);
	y = data->player.move_speed * sin(data->player.rotation_angle);
	if (hit_wall(data, data->player.x + x, data->player.y + y) == 0)
	{
		data->player.x += x;
		data->player.y += y;
	}
}

void	back_move(t_data *data)
{
	int	x;
	int	y;

	x = data->player.move_speed * cos(data->player.rotation_angle);
	y = data->player.move_speed * sin(data->player.rotation_angle);
	if (hit_wall(data, data->player.x - x, data->player.y - y) == 0)
	{
		data->player.x -= x;
		data->player.y -= y;
	}
}

void	left_move(t_data *data)
{
	int	x;
	int	y;

	x = data->player.move_speed * cos(data->player.rotation_angle - M_PI_2);
	y = data->player.move_speed * sin(data->player.rotation_angle - M_PI_2);
	if (hit_wall(data, data->player.x + x, data->player.y + y) == 0)
	{
		data->player.x += x;
		data->player.y += y;
	}
}

void	right_move(t_data *data)
{
	int	x;
	int	y;

	x = data->player.move_speed * cos(data->player.rotation_angle + M_PI_2);
	y = data->player.move_speed * sin(data->player.rotation_angle + M_PI_2);
	if (hit_wall(data, data->player.x + x, data->player.y + y) == 0)
	{
		data->player.x += x;
		data->player.y += y;
	}
}

int	movement(int key, t_data *data)
{
	if (key == 126 || key == 13)
		front_move(data);
	else if (key == 125 || key == 1)
		back_move(data);
	else if (key == 2)
		right_move(data);
	else if (key == 0)
		left_move(data);
	else if (key == 124)
		data->player.rotation_angle += data->player.rotation_speed;
	else if (key == 123)
		data->player.rotation_angle -= data->player.rotation_speed;
	else if (key == 53)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	draw(data);
	return (0);
}
