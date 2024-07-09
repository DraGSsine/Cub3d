/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:51:56 by youchen           #+#    #+#             */
/*   Updated: 2024/07/09 18:51:02 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void ft_draw(t_data *data, int x, int y, int color)
{
    mlx_put_pixel(data->imgs.mini, x , y , color);
}


void    ft_draw_line(int x1, int y1, int x2, int y2, t_data *cub, u_int32_t color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx;
    int sy;
    int err;
    int e2;

    sx = (x1 < x2) ? 1 : -1;
    sy = (y1 < y2) ? 1 : -1;
    err = dx - dy;

    while (true)
    {
        if (!(x1 < 0 || y1 < 0 || x1 > WIN_WIDTH_MINI || y1 > WIN_HEIGHT_MINI))
            mlx_put_pixel(cub->imgs.mini, x1, y1, color);

        if (x1 == x2 && y1 == y2)
            break;

        e2 = 2 * err;
        
        if (e2 > -dy) 
        {
            err -= dy;
            x1 += sx;
        }
        
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}


void    ft_draw_line2(int x2, int y2, t_data *cub)
{
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;
    int    x1;
    int    y1;
    x1 = WIN_WIDTH_MINI / 2;
    y1 = WIN_HEIGHT_MINI / 2;
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    int radius = WIN_WIDTH_MINI / 2;
    sx = (x1 < x2) ? 1 : -1;
    sy = (y1 < y2) ? 1 : -1;
    err = dx - dy;
    while (true)
    {
        if (x1 >= 0 && y1 >= 0 && x1 < WIN_WIDTH_MINI && y1 < WIN_HEIGHT_MINI && (pow(x1 - radius, 2) + pow(y1 - radius, 2) < pow(radius, 2)))
        {
                if (x1 < 0 || y1 < 0 || x1 >= WIN_WIDTH_MINI || y1 >= WIN_HEIGHT_MINI)
                    break;
                mlx_put_pixel(cub->imgs.mini, x1, y1, 0xA6A600FF);
        }

        if (x1 == x2 && y1 == y2)
            break;
        e2 = 2 * err;
        if (e2 > -dy) 
        {
            err -= dy;
            x1 += sx;
        }
        
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void    ft_draw_rays_minimap(t_data *cub)
{
    int    x2, y2;
    double    ray_distance = 0;

    for (int i = 0; i < WIN_WIDTH; i++)
    {
        ray_distance = (cub->rays[i].distance * MINI_TILE_SIZE) / TILE_SIZE;
        x2 = WIN_WIDTH_MINI / 2 + (ray_distance) * cos(cub->rays[i].ray_angle);
        y2 = WIN_HEIGHT_MINI / 2 + (ray_distance) * sin(cub->rays[i].ray_angle);
        ft_draw_line2(x2, y2, cub);
    }
}



void    ft_draw_player_2(t_data *cub)
{
    int    x;
    int    y;
    int    radius;
    float px, py;

    px = 300/2;
    py = 300/2;
    x = (px + 20 * cos(cub->player.rotation_angle));
    y = (py + 20 * sin(cub->player.rotation_angle));
    ft_draw_line(px, py, x, y, cub, 0x000000FF);
    radius = 5;
    y = py - radius;
    while (y < py + radius)
    {
        x = px - radius;
        while (x < px + radius)
        {
            if (pow(x - px, 2) + pow(y - py, 2) < pow(radius, 2) )
                mlx_put_pixel(cub->imgs.mini, x, y, 0xFF4545FF);
            x++;
        }
        y++;
    }
}
void ft_mini_map(t_data *data, int x, int y)
{
    int px;
    int py;
    int i;
    int j;
    int radius;

    i = 0;
    radius = WIN_WIDTH_MINI / 2;
    py = y - radius;
    while (py < y + radius)
    { 
        j = 0;
        px = x - radius;
        while (px < x + radius)
        {
            if (px >= 0 && py >= 0 && px < data->map_info.width_map * MINI_TILE_SIZE && py < data->map_info.height_map * MINI_TILE_SIZE && pow(px - x, 2) + pow(py - y, 2) < pow(radius, 2))
            {
    
                if (data->map_info.map[py / MINI_TILE_SIZE][px / MINI_TILE_SIZE] == '1')
                    ft_draw(data, j, i, 0x004DFF);
                else if (data->map_info.map[py / MINI_TILE_SIZE][px / MINI_TILE_SIZE] == '0')
                    ft_draw(data, j, i, 0xFFFFFFFF);
                else
                    ft_draw(data, j, i, 0xFF0000FF);
                if (data->map_info.map[py / MINI_TILE_SIZE][px / MINI_TILE_SIZE] == data->player.position_side)
                    ft_draw(data, j, i, 0xFFFFFFFF);
            }
            else if (pow(px - x, 2) + pow(py - y, 2) < pow(radius, 2))
                    ft_draw(data, j, i, 0xFF0000FF);
            px++;
            j++;
        }
        py++;
        i++;
    }
    ft_draw_rays_minimap(data);
    ft_draw_player_2(data);
}

void	draw(void *arg)
{
	t_data	*data;
	data = arg;
	
	
	if (data->rand)
	{
		cast_all_rays(data, data->rays);
		render_walls(data, data->rays);
        ft_mini_map(data, (data->player.x / TILE_SIZE) * MINI_TILE_SIZE, (data->player.y / TILE_SIZE) * MINI_TILE_SIZE);
		data->rand = false;
	}
}

int	main(int ac ,char **av)
{
	t_data	data;

	read_file_parse(ac, av, &data);
	print_texture(&data.map_info, &data);
    mlx_image_to_window(data.imgs.mlx, data.imgs.map, 0, 0);
    mlx_image_to_window(data.imgs.mlx, data.imgs.mini, 650, 700);
	mlx_loop_hook(data.imgs.mlx, movement, &data);
	mlx_loop(data.imgs.mlx);
	
	return (0);
}
