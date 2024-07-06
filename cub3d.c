/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:51:56 by youchen           #+#    #+#             */
/*   Updated: 2024/07/06 20:38:42 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void ft_draw(t_data *data, int x, int y, int color)
{
    int l = 0;
    while ( l < MINI_TILE_SIZE)
    {
        int k = 0;
        while (k < MINI_TILE_SIZE)
        {
            mlx_put_pixel(data->imgs.minimap, x + k, y + l, color);
            k++;
        }
        l++;
    }
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
            mlx_put_pixel(cub->imgs.minimap, x1, y1, color);

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


void    ft_draw_player(t_data *cub)
{
    int    x;
    int    y;
    int    radius;
    float px, py;

    px = (cub->player.x / TILE_SIZE) * MINI_TILE_SIZE;
    py = (cub->player.y / TILE_SIZE) * MINI_TILE_SIZE;
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
                mlx_put_pixel(cub->imgs.minimap, x, y, 0xFF4545);
            x++;
        }
        y++;
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
    x1 = (cub->player.x / TILE_SIZE) * MINI_TILE_SIZE;
    y1 = (cub->player.y / TILE_SIZE) * MINI_TILE_SIZE;
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    sx = (x1 < x2) ? 1 : -1;
    sy = (y1 < y2) ? 1 : -1;
    err = dx - dy;
    while (true)
    {
        if (x1 >= 0 && y1 >= 0 && x1 < cub->map_info.width_map * MINI_TILE_SIZE && y1 < cub->map_info.height_map * MINI_TILE_SIZE)
        {
                if (x1 < 0 || y1 < 0 || x1 >= WIN_WIDTH_MINI || y1 >= WIN_HEIGHT_MINI)
                    break;
                if (cub->map_info.map[y1 / MINI_TILE_SIZE][x1 / MINI_TILE_SIZE] == '1')
                    break;
                mlx_put_pixel(cub->imgs.minimap, x1, y1, 0xA6A600FF);
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
    float    ray_distance;

    for (int i = 0; i < WIN_WIDTH; i++)
    {
        ray_distance = cub->rays[i].distance;
        x2 = ((cub->player.x /TILE_SIZE) * MINI_TILE_SIZE) + (ray_distance - 1) * cos(cub->rays[i].ray_angle);
        y2 = ((cub->player.y / TILE_SIZE) * MINI_TILE_SIZE) + (ray_distance - 1) * sin(cub->rays[i].ray_angle);
        ft_draw_line2(x2, y2, cub);
    }
}


void ft_rander(void *cub)
{
    int i;
    int j;
    t_data *data;
    
    data = (t_data *)cub;
    i = 0;
    while (i < data->map_info.height_map)
    {
        j = 0;
        while (j < data->map_info.width_map)
        {
            if (data->map_info.map[i][j] == '1')
                ft_draw(data, j* MINI_TILE_SIZE, i * MINI_TILE_SIZE, 0x004DFF);
            else if (data->map_info.map[i][j] == '0')
                ft_draw(data, j * MINI_TILE_SIZE, i * MINI_TILE_SIZE, 0xFFFFFFFF);
            if (data->map_info.map[i][j] == data->player.position_side)
                    ft_draw(data, j * MINI_TILE_SIZE, i * MINI_TILE_SIZE, 0xFFFFFFFF);
            j++;
        }
        i++;
    }
    ft_draw_rays_minimap(data);
    ft_draw_player(data);
}

void	draw(void *arg)
{
	t_data	*data;
	data = arg;
	
	
	if (data->rand)
	{
		
		cast_all_rays(data, data->rays);
		render_walls(data, data->rays);
        ft_rander(data);
		data->rand = false;
	}
}

int	main(int ac ,char **av)
{
	t_data	data;

	read_file_parse(ac, av, &data);
	print_texture(&data.map_info, &data);
	mlx_image_to_window(data.imgs.mlx, data.imgs.minimap, 0, 0);
    mlx_image_to_window(data.imgs.mlx, data.imgs.map, WIN_WIDTH_MINI, 0);
    
	mlx_loop_hook(data.imgs.mlx, movement, &data);
	mlx_loop(data.imgs.mlx);
	
	return (0);
}
