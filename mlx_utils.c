/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:20:41 by youchen           #+#    #+#             */
/*   Updated: 2024/07/03 11:55:58 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	// *(unsigned int *)(data->img.addr + (y * data->img.line_length + x
	// 			* (data->img.bits_per_pixel / 8))) = color;
	data->imgs.map->pixels[(y * data->imgs.map->height + x * 4) * 4] = color;
}

// int	close_window(t_data *data)
// {
// 	// mlx_destroy_window(data->, data->mlx_win);
// 	exit(0);
// 	return (0);
// }
