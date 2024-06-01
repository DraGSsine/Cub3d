/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchen <youchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:51:56 by youchen           #+#    #+#             */
/*   Updated: 2024/06/01 12:06:13 by youchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_data *data)
{
	t_ray	rays[MAP_WIDTH * TILE_SIZE];

	cast_all_rays(data, rays);
	render_walls(data, rays);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

int	main(void)
{
	t_data	data;

	init_game(&data);
	draw(&data);
	mlx_hook(data.mlx_win, 2, 0, movement, &data);
	mlx_hook(data.mlx_win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
