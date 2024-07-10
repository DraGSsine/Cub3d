/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:28:30 by youchen           #+#    #+#             */
/*   Updated: 2024/07/10 17:40:51 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	front_move(t_data *data)
{
	int	x;
	int	y;

	x = data->player.move_speed * cos(data->player.rotation_angle);
	y = data->player.move_speed * sin(data->player.rotation_angle);
	if (hit_wall(data, data->player.x + x * LIMIT, data->player.y + y * LIMIT) == 0)
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
	if (hit_wall(data, data->player.x - x * LIMIT, data->player.y - y * LIMIT) == 0)
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
	if (hit_wall(data, data->player.x + x * LIMIT, data->player.y + y * LIMIT) == 0)
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
	if (hit_wall(data, data->player.x + x * LIMIT, data->player.y + y * LIMIT) == 0)
	{
		data->player.x += x;
		data->player.y += y;
	}
}

void	movement(void *arg)
{
	t_data	*data;
	data = arg;
	if ( mlx_is_key_down(data->imgs.mlx, MLX_KEY_W) || mlx_is_key_down(data->imgs.mlx, MLX_KEY_UP))
	{
		front_move(data);
		data->rand = 1;
	}
	if (mlx_is_key_down(data->imgs.mlx, MLX_KEY_S) || mlx_is_key_down(data->imgs.mlx, MLX_KEY_DOWN))
	{
		data->rand = 1;
		back_move(data);
	}
	if (mlx_is_key_down(data->imgs.mlx, MLX_KEY_D))
	{
		data->rand = 1;	
		right_move(data);
	}
	if (mlx_is_key_down(data->imgs.mlx, MLX_KEY_A))
	{
		data->rand = 1;
		left_move(data);
	}
	if (mlx_is_key_down(data->imgs.mlx, MLX_KEY_LEFT))
	{
		data->rand = 1;
		data->player.rotation_angle -= data->player.rotation_speed;
		data->player.rotation_angle = normalize_angle(data->player.rotation_angle);
	}
	if (mlx_is_key_down(data->imgs.mlx, MLX_KEY_RIGHT))
	{
		data->rand = 1;
		data->player.rotation_angle += data->player.rotation_speed;
		data->player.rotation_angle = normalize_angle(data->player.rotation_angle);
	}
	if (mlx_is_key_down(data->imgs.mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->imgs.mlx);
		exit(0);
	}
	if (data->rand)
		draw(data);
	
}