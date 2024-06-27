/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:51:56 by youchen           #+#    #+#             */
/*   Updated: 2024/06/27 10:15:38 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_data *data)
{
	t_ray	rays[data->map_info.width_map * TILE_SIZE];

	cast_all_rays(data, rays);
	render_walls(data, rays);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

int	main(int ac, char **av)
{
	t_data	data;

	read_file_parse(ac, av, &data);
	print_texture(&data.map_info);
	init_game(&data);
	draw(&data);
	mlx_hook(data.mlx_win, 2, 0, movement, &data);
	mlx_hook(data.mlx_win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
