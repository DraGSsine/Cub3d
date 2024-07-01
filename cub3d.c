/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:51:56 by youchen           #+#    #+#             */
/*   Updated: 2024/06/30 10:31:27 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void draw_square(t_data *data, int x, int y, int color)
// {
//     int    i;
//     int    j;

//     i = 0;
//     while (i < TILE_SIZE)
//     {
//         j = 0;
//         while (j < TILE_SIZE)
//         {
//             my_mlx_pixel_put(data, x + i, y + j, color);
//             j++;
//         }
//         i++;
//     }
// }

// void draw2dmap(t_data *data)
// {
//     int    x;
//     int    y;

//     y = 0;
//     while (y < data->map_info.height_map)
//     {
//         x = 0;
//         while (x < data->map_info.width_map)
//         {
//             if (data->map_info.map[y][x] == '1')
//                 draw_square(data, x * TILE_SIZE, y * TILE_SIZE, 0x00FF0000);
//             else
//                 draw_square(data, x * TILE_SIZE, y * TILE_SIZE, 0x00000000);
//             x++;
//         }
//         y++;
//     }

// }

// void drawplayer(t_data *data)
// {
//     my_mlx_pixel_put(data, data->player.x, data->player.y, 0xFFFF00);
// }

void	draw(t_data *data)
{
	t_ray	rays[MAP_WIDTH];
	cast_all_rays(data, rays);
	render_walls(data, rays);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}

int	main(int ac ,char **av)
{
	t_data	data;

	read_file_parse(ac, av, &data);
	print_texture(&data.map_info);
	printf("player info\n");
	printf("x: %f\n", data.player.x);
	printf("y: %f\n", data.player.y);
	printf("fov: %f\n", data.player.fov);
	printf("move_speed: %f\n", data.player.move_speed);
	printf("rotation_speed: %f\n", data.player.rotation_speed);
	printf("rotation_angle: %f\n", data.player.rotation_angle);
	printf("position_side: %d\n", data.player.position_side);
	
	draw(&data);
	mlx_hook(data.mlx_win, 2, 0, movement, &data);
	mlx_hook(data.mlx_win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
